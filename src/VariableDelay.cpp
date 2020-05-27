#include "VariableDelay.hpp"
#include <cassert>

using md_audio::MdFloat;
using md_audio::VariableDelay;

VariableDelay::VariableDelay(memory::Poolable& pool, MdFloat max_delay, std::size_t overlap) :
    m_pool(pool),
    m_delay(pool, max_delay, overlap),
    m_overlap(overlap),
    m_norm(static_cast<MdFloat>(2) / overlap)
{
    assert(m_overlap > 1);

    initialise(static_cast<MdFloat>(1), static_cast<MdFloat>(1));
}

VariableDelay::VariableDelay(
    memory::Poolable& pool,
    MdFloat max_delay,
    MdFloat delay,
    std::size_t overlap
) :
    m_pool(pool),
    m_delay(pool, max_delay, overlap),
    m_overlap(overlap),
    m_norm(static_cast<MdFloat>(2) / overlap)
{
    assert(m_overlap > 1);

    initialise(delay, static_cast<MdFloat>(1));
}

VariableDelay::VariableDelay(
    memory::Poolable& pool,
    MdFloat max_delay,
    MdFloat delay,
    MdFloat size,
    std::size_t overlap
) :
    m_pool(pool),
    m_delay(pool, max_delay, overlap),
    m_overlap(overlap),
    m_norm(static_cast<MdFloat>(2) / overlap)
{
    assert(m_overlap > 1);

    initialise(delay, size);
}

void VariableDelay::initialise() {
    m_delay.initialise();
}

void VariableDelay::initialise(MdFloat delay, MdFloat size) {
    m_phasor = static_cast<Phasor*>(allocate(sizeof(Phasor)));
    m_osc = static_cast<HannOscillator*>(allocate(sizeof(HannOscillator)));
    m_latch = static_cast<Latch*>(allocate(sizeof(Latch)));

    set_delay(delay);
    set_size(size);

    for (auto i = 0; i < m_overlap; ++i) {
        m_phasor[i].set_phase(static_cast<MdFloat>(i) / static_cast<MdFloat>(m_overlap));
        m_osc[i].set_frequency(static_cast<MdFloat>(0));
    }
}

void* VariableDelay::allocate(std::size_t size) {
    auto memory = m_pool.allocate(m_overlap * size);

    if (!memory) throw std::bad_alloc();

    return memory;
}

void VariableDelay::set_size(MdFloat size) noexcept {
    size = utility::clip(size, static_cast<MdFloat>(5), m_delay.get_max_delay());

    auto frequency = compute_frequency(size);

    for (auto i = 0; i < m_overlap; ++i)
        m_phasor[i].set_frequency(frequency);
}

MdFloat VariableDelay::perform(MdFloat in) noexcept {
    auto z = static_cast<MdFloat>(0);

    for (auto i = 0; i < m_overlap; ++i) {
        auto phase = m_phasor[i].perform();

        m_osc[i].set_phase(static_cast<MdFloat>(phase * two_pi));

        auto window = m_osc[i].perform();
        auto delay = m_latch[i].perform(m_delay_samples, phase);

        m_delay.set_delay(i, delay);

        z += m_delay.read(i) * window;
    }

    m_delay.write(in); // Write the next sample to the delay buffer

    return z * m_norm;
}

VariableDelay::~VariableDelay() {
    if (m_phasor) m_pool.deallocate(m_phasor);
    if (m_osc) m_pool.deallocate(m_osc);
    if (m_latch) m_pool.deallocate(m_latch);
}
