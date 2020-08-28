#include "PitchShifter.hpp"
#include "utility"

using md_audio::MdFloat;
using md_audio::PitchShifter;

PitchShifter::PitchShifter(
    memory::Poolable& pool,
    MdFloat max_size,
    MdFloat size,
    std::size_t overlap
) :
    m_max_size(max_size),
    m_overlap(utility::max<size_t>(overlap, 2)),
    m_norm(static_cast<MdFloat>(2) / m_overlap),
    m_pool(pool),
    m_delay(pool, max_size, m_overlap)
{
    initialise(size, static_cast<MdFloat>(0));
}

PitchShifter::PitchShifter(
    memory::Poolable& pool,
    MdFloat max_size,
    MdFloat size,
    MdFloat transposition,
    std::size_t overlap
) :
    m_max_size(max_size),
    m_overlap(utility::max<size_t>(overlap, 2)),
    m_norm(static_cast<MdFloat>(2) / m_overlap),
    m_pool(pool),
    m_delay(pool, m_max_size, m_overlap)
{
    initialise(size, transposition);
}

void PitchShifter::initialise(MdFloat size, MdFloat transposition) {
    m_phasor = static_cast<Phasor*>(m_pool.allocate(m_overlap * sizeof(Phasor)));
    m_osc = static_cast<HannOscillator*>(m_pool.allocate(m_overlap * sizeof(HannOscillator)));
    m_size = check_size(size);
    m_transposition = check_transposition(transposition);

    set_frequency();

    for (std::uint32_t i = 0; i < m_overlap; ++i) {
        m_phasor[i].set_phase(
            static_cast<MdFloat>(1) - static_cast<MdFloat>(i) / static_cast<MdFloat>(m_overlap)
        );
        m_osc[i].set_frequency(static_cast<MdFloat>(0));
    }
}

void PitchShifter::set_size(MdFloat size) noexcept {
    m_size = check_size(size);

    set_frequency();
}

void PitchShifter::set_frequency() noexcept {
    auto frequency = compute_frequency(m_transposition, m_size);

    for (std::uint32_t i = 0; i < m_overlap; ++i)
        m_phasor[i].set_frequency(frequency);
}

MdFloat PitchShifter::perform(MdFloat in) noexcept {
    auto z = static_cast<MdFloat>(0);

    for (std::uint32_t i = 0; i < m_overlap; ++i) {
        auto phase = m_phasor[i].perform();

        m_osc[i].set_phase(static_cast<MdFloat>(phase * two_pi));

        auto window = m_osc[i].perform();

        m_delay.set_delay(i, phase * m_size);

        z += m_delay.read(i) * window;
    }

    m_delay.write(in); // Write the next sample to the delay buffer

    return z * m_norm;
}

void PitchShifter::set_sample_rate(double sample_rate) noexcept {
    SampleRate::set_sample_rate(sample_rate);
}

PitchShifter::~PitchShifter() {
    if (m_phasor) m_pool.deallocate(m_phasor);
    if (m_osc) m_pool.deallocate(m_osc);
}
