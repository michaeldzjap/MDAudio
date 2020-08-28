#include "VariableDelay.hpp"
#include "utility.hpp"

using md_audio::MdFloat;
using md_audio::VariableDelay;

VariableDelay::VariableDelay(
    memory::Poolable& pool,
    MdFloat max_delay,
    std::size_t overlap
) :
    m_max_delay(max_delay),
    m_overlap(utility::max<size_t>(overlap, 2)),
    m_norm(static_cast<MdFloat>(2) / m_overlap),
    m_pool(pool),
    m_delay(pool, max_delay, m_overlap)
{
    initialise(static_cast<MdFloat>(1), static_cast<MdFloat>(1));
}

VariableDelay::VariableDelay(
    memory::Poolable& pool,
    MdFloat max_delay,
    MdFloat delay,
    std::size_t overlap
) :
    m_max_delay(max_delay),
    m_overlap(utility::max<size_t>(overlap, 2)),
    m_norm(static_cast<MdFloat>(2) / m_overlap),
    m_pool(pool),
    m_delay(pool, max_delay, m_overlap)
{
    initialise(delay, static_cast<MdFloat>(1));
}

VariableDelay::VariableDelay(
    memory::Poolable& pool,
    MdFloat max_delay,
    MdFloat delay,
    MdFloat size,
    std::size_t overlap
) :
    m_max_delay(max_delay),
    m_overlap(utility::max<size_t>(overlap, 2)),
    m_norm(static_cast<MdFloat>(2) / m_overlap),
    m_pool(pool),
    m_delay(pool, max_delay, m_overlap)
{
    initialise(delay, size);
}

void VariableDelay::initialise(MdFloat delay, MdFloat size) {
    m_phasor = static_cast<Phasor*>(m_pool.allocate(m_overlap * sizeof(Phasor)));
    m_osc = static_cast<HannOscillator*>(m_pool.allocate(m_overlap * sizeof(HannOscillator)));
    m_latch = static_cast<Latch*>(m_pool.allocate(m_overlap * sizeof(Latch)));

    set_delay(delay);
    set_size(size);

    for (std::uint32_t i = 0; i < m_overlap; ++i) {
        m_phasor[i].set_phase(static_cast<MdFloat>(i) / static_cast<MdFloat>(m_overlap));
        m_osc[i].set_frequency(static_cast<MdFloat>(0));
    }
}

void VariableDelay::set_size(MdFloat size) noexcept {
    size = utility::clip(size, static_cast<MdFloat>(.01), m_max_delay);

    auto frequency = compute_frequency(size);

    for (std::uint32_t i = 0; i < m_overlap; ++i)
        m_phasor[i].set_frequency(frequency);
}

MdFloat VariableDelay::perform(MdFloat in) noexcept {
    auto z = static_cast<MdFloat>(0);

    for (std::uint32_t i = 0; i < m_overlap; ++i) {
        auto phase = m_phasor[i].perform();

        m_osc[i].set_phase(static_cast<MdFloat>(phase * two_pi));

        auto window = m_osc[i].perform();
        auto delay = m_latch[i].perform(m_delay_time, phase);

        m_delay.set_delay(i, delay);

        z += m_delay.read(i) * window;
    }

    m_delay.write(in); // Write the next sample to the delay buffer

    return z * m_norm;
}

void VariableDelay::set_sample_rate(double sample_rate) noexcept {
    SampleRate::set_sample_rate(sample_rate);
}

VariableDelay::~VariableDelay() {
    if (m_phasor) m_pool.deallocate(m_phasor);
    if (m_osc) m_pool.deallocate(m_osc);
    if (m_latch) m_pool.deallocate(m_latch);
}
