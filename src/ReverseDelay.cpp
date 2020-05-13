#include "ReverseDelay.hpp"
#include <cassert>

using md_audio::MdFloat;
using md_audio::ReverseDelay;

ReverseDelay::ReverseDelay(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay,
    std::size_t overlap, InterpolationType interpolation_type) :
    m_delay(allocator, max_delay, overlap, interpolation_type),
    m_overlap(overlap),
    m_norm(static_cast<MdFloat>(2) / overlap),
    m_phasor(new Phasor[overlap]),
    m_osc(new HannOscillator[overlap])
{
    assert(m_overlap > 1);

    initialise(static_cast<MdFloat>(1));
}

ReverseDelay::ReverseDelay(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay,
    MdFloat size, std::size_t overlap, InterpolationType interpolation_type) :
    m_delay(allocator, max_delay, overlap, interpolation_type),
    m_overlap(overlap),
    m_norm(static_cast<MdFloat>(2) / overlap),
    m_phasor(new Phasor[overlap]),
    m_osc(new HannOscillator[overlap])
{
    assert(m_overlap > 1);

    initialise(size);
}

void ReverseDelay::initialise() {
    m_delay.initialise();
}

void ReverseDelay::initialise(MdFloat size) noexcept {
    set_size(size);

    for (auto i = 0; i < m_overlap; ++i)
        m_phasor[i].set_phase(static_cast<MdFloat>(i) / static_cast<MdFloat>(m_overlap));
}

void ReverseDelay::set_size(MdFloat size) noexcept {
    m_size = utility::clip(size, static_cast<MdFloat>(5), m_delay.get_max_delay());

    auto frequency = compute_frequency(m_size);

    for (auto i = 0; i < m_overlap; ++i)
        m_phasor[i].set_frequency(frequency);
}

MdFloat ReverseDelay::perform(MdFloat in) noexcept {
    auto z = static_cast<MdFloat>(0);

    for (auto i = 0; i < m_overlap; ++i) {
        auto phase = m_phasor[i].perform();

        m_osc[i].set_phase(static_cast<MdFloat>(phase * two_pi));

        auto window = m_osc[i].perform();

        m_delay.set_delay(i, phase * m_size);

        z += m_delay.read(i) * window;
    }

    m_delay.write(in); // Write the next sample to the delay buffer

    return z * m_norm;
}

ReverseDelay::~ReverseDelay() {
    delete[] m_phasor;
    delete[] m_osc;
}
