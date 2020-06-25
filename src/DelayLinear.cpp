#include "DelayLinear.hpp"

using md_audio::DelayLinear;
using md_audio::MdFloat;

DelayLinear::DelayLinear(memory::Poolable& pool, MdFloat max_delay) :
    m_max_delay(static_cast<std::uint32_t>(sample_rate * max_delay) + 2),
    m_buffer(pool, m_max_delay),
    m_reader(m_buffer, m_max_delay - 1),
    m_writer(m_buffer, m_max_delay - 1)
{
    m_buffer.initialise();

    set_delay(static_cast<MdFloat>(1));
}

DelayLinear::DelayLinear(memory::Poolable& pool, MdFloat max_delay, MdFloat delay) :
    m_max_delay(static_cast<std::uint32_t>(sample_rate * max_delay) + 2),
    m_buffer(pool, m_max_delay),
    m_reader(m_buffer, m_max_delay - 1),
    m_writer(m_buffer, m_max_delay - 1)
{
    m_buffer.initialise();

    set_delay(delay);
}

MdFloat DelayLinear::perform(MdFloat in) noexcept {
    auto z = m_reader.read(m_writer, m_delay, m_frac);

    m_writer.write(in);

    return z;
}
