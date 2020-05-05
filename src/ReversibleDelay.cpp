#include "ReversibleDelay.hpp"
#include <cassert>

using md_audio::MdFloat;
using md_audio::ReversibleDelay;

ReversibleDelay::ReversibleDelay(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay,
    std::size_t overlap, InterpolationType interpolation_type) :
    m_delay(allocator, max_delay, overlap + 1, interpolation_type),
    m_overlap(overlap),
    m_reverse(false),
    m_norm(static_cast<MdFloat>(2) / overlap),
    m_phasor(new Phasor[overlap]),
    m_osc(new HannOscillator[overlap])
{
    assert(m_overlap > 1);

    initialise(static_cast<MdFloat>(0));
}

ReversibleDelay::ReversibleDelay(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay,
    MdFloat size, std::size_t overlap, InterpolationType interpolation_type) :
    m_delay(allocator, max_delay, overlap + 1, interpolation_type),
    m_overlap(overlap),
    m_reverse(false),
    m_norm(static_cast<MdFloat>(2) / overlap),
    m_phasor(new Phasor[overlap]),
    m_osc(new HannOscillator[overlap])
{
    assert(m_overlap > 1);

    initialise(size);
}

ReversibleDelay::ReversibleDelay(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay,
    MdFloat size, bool reverse, std::size_t overlap, InterpolationType interpolation_type) :
    m_delay(allocator, max_delay, overlap + 1, interpolation_type),
    m_overlap(overlap),
    m_reverse(reverse),
    m_norm(static_cast<MdFloat>(2) / overlap),
    m_phasor(new Phasor[overlap]),
    m_osc(new HannOscillator[overlap])
{
    assert(m_overlap > 1);

    initialise(size);
}

void ReversibleDelay::initialise() {
    m_delay.initialise();
}

void ReversibleDelay::initialise(MdFloat size) noexcept {
    set_forward_delay(size);
    set_backward_delay(size);

    for (auto i = 0; i < m_overlap; i++)
        m_phasor[i].set_phase(static_cast<MdFloat>(i) / static_cast<MdFloat>(m_overlap));
}

void ReversibleDelay::set_backward_delay(MdFloat size) noexcept {
    m_size = utility::clip(size, static_cast<MdFloat>(5), m_delay.get_max_delay());

    m_frequency = compute_frequency(m_size);

    for (auto i = 0; i < m_overlap; i++)
        m_phasor[i].set_frequency(m_frequency);
}

void ReversibleDelay::set_forward_delay(MdFloat delay) noexcept {
    m_delay.set_delay(m_overlap, delay);
}

MdFloat ReversibleDelay::perform(MdFloat in) noexcept {
    auto z = static_cast<MdFloat>(0);

    if (m_reverse) {
        for (auto i = 0; i < m_overlap; i++) {
            auto phase = m_phasor[i].perform();

            m_osc[i].set_phase(static_cast<MdFloat>(phase * two_pi));

            auto window = m_osc[i].perform();

            m_delay.set_delay(i, phase * m_size);

            z += m_delay.read(i) * window;
        }

        z *= m_norm;
    } else
        z = m_delay.read(m_overlap);

    m_delay.write(in); // Write the next sample to the delay buffer

    return z;
}

ReversibleDelay::~ReversibleDelay() {
    delete[] m_phasor;
    delete[] m_osc;
}
