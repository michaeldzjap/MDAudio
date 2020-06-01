#include "DelayLinear.hpp"

using md_audio::DelayLinear;
using md_audio::MdFloat;

DelayLinear::DelayLinear(memory::Poolable& pool, std::size_t max_delay) :
    m_buffer(pool, max_delay),
    m_reader(m_buffer, max_delay - 1),
    m_writer(m_buffer, max_delay - 1),
    m_max_delay(static_cast<MdFloat>(max_delay - 1))
{
    m_buffer.initialise();

    set_delay(static_cast<MdFloat>(1));
}

DelayLinear::DelayLinear(memory::Poolable& pool, std::size_t max_delay, MdFloat delay) :
    m_buffer(pool, max_delay),
    m_reader(m_buffer, max_delay - 1),
    m_writer(m_buffer, max_delay - 1),
    m_max_delay(static_cast<MdFloat>(max_delay - 1))
{
    m_buffer.initialise();

    set_delay(delay);
}

MdFloat DelayLinear::perform(MdFloat in) noexcept {
    m_writer.write(in);

    auto z = m_reader.read(m_writer, m_delay, m_frac);

    return z;
}
