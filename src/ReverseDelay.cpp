#include "ReverseDelay.hpp"
#include <cassert>
#include <new>

using md_audio::MdFloat;
using md_audio::ReverseDelay;

ReverseDelay::ReverseDelay(
    memory::Poolable& pool,
    MdFloat max_delay,
    std::size_t overlap
) :
    m_max_delay(max_delay),
    m_overlap(overlap),
    m_norm(static_cast<MdFloat>(2) / m_overlap),
    m_pool(pool),
    m_delay(pool, max_delay, m_overlap)
{
    assert(m_overlap > 1);

    initialise(static_cast<MdFloat>(1));
}

ReverseDelay::ReverseDelay(
    memory::Poolable& pool,
    MdFloat max_delay,
    MdFloat size,
    std::size_t overlap
) :
    m_max_delay(max_delay),
    m_overlap(overlap),
    m_norm(static_cast<MdFloat>(2) / m_overlap),
    m_pool(pool),
    m_delay(pool, max_delay, m_overlap)
{
    assert(m_overlap > 1);

    initialise(size);
}

void ReverseDelay::initialise(MdFloat size) {
    m_phasor = static_cast<Phasor*>(m_pool.allocate(m_overlap * sizeof(Phasor)));
    m_osc = static_cast<HannOscillator*>(m_pool.allocate(m_overlap * sizeof(HannOscillator)));

    set_size(size);

    for (std::uint32_t i = 0; i < m_overlap; ++i) {
        m_phasor[i].set_phase(static_cast<MdFloat>(i) / static_cast<MdFloat>(m_overlap));
        m_osc[i].set_frequency(static_cast<MdFloat>(0));
    }
}

void ReverseDelay::set_size(MdFloat size) noexcept {
    m_size = utility::clip(size, static_cast<MdFloat>(.01), m_max_delay);

    auto frequency = compute_frequency(m_size);

    for (std::uint32_t i = 0; i < m_overlap; ++i)
        m_phasor[i].set_frequency(frequency);
}

MdFloat ReverseDelay::perform(MdFloat in) noexcept {
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

ReverseDelay::~ReverseDelay() {
    if (m_phasor) m_pool.deallocate(m_phasor);
    if (m_osc) m_pool.deallocate(m_osc);
}
