#include "PitchShifter.hpp"

using md_audio::MdFloat;
using md_audio::PitchShifter;

PitchShifter::PitchShifter(memory::Allocatable<MdFloat*>& allocator,
    MdFloat max_delay, MdFloat size, std::size_t overlap, InterpolationType interpolation_type) :
    m_delay(allocator, max_delay, overlap, interpolation_type),
    m_overlap(overlap),
    m_norm(static_cast<MdFloat>(2) / m_overlap),
    m_phasor(new Phasor[overlap]),
    m_osc(new HannOscillator[overlap])
{
    initialise(size, static_cast<MdFloat>(1));
}

PitchShifter::PitchShifter(memory::Allocatable<MdFloat*>& allocator,
    MdFloat max_delay, MdFloat size, MdFloat transposition, std::size_t overlap,
    InterpolationType interpolation_type) :
    m_delay(allocator, max_delay, overlap, interpolation_type),
    m_overlap(overlap),
    m_norm(static_cast<MdFloat>(2) / m_overlap),
    m_phasor(new Phasor[overlap]),
    m_osc(new HannOscillator[overlap])
{
    initialise(size, transposition);
}

void PitchShifter::initialise() {
    m_delay.initialise();
}

void PitchShifter::initialise(MdFloat size, MdFloat transposition) noexcept {
    m_size = check_size(size);
    m_transposition = check_transposition(transposition);

    set_frequency();

    for (auto i = 0; i < m_overlap; i++)
        m_phasor[i].set_phase(
            static_cast<MdFloat>(1) - static_cast<MdFloat>(i) / static_cast<MdFloat>(m_overlap)
        );
}

void PitchShifter::set_size(MdFloat size) noexcept {
    m_size = check_size(size);

    set_frequency();
}

void PitchShifter::set_frequency() noexcept {
    auto frequency = compute_frequency(m_transposition, m_size);

    for (auto i = 0; i < m_overlap; i++)
        m_phasor[i].set_frequency(frequency);
}

MdFloat PitchShifter::perform(MdFloat in) noexcept {
    auto z = static_cast<MdFloat>(0);

    for (auto i = 0; i < m_overlap; i++) {
        auto phase = m_phasor[i].perform();

        m_osc[i].set_phase(static_cast<MdFloat>(phase * two_pi));

        auto window = m_osc[i].perform();

        m_delay.set_delay(i, phase * m_size);

        z += m_delay.read(i) * window;
    }

    m_delay.write(in); // Write the next sample to the delay buffer

    return z * m_norm;
}

PitchShifter::~PitchShifter() {
    delete[] m_phasor;
    delete[] m_osc;
}
