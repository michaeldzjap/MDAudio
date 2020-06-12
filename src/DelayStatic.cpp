#include "DelayStatic.hpp"

using md_audio::DelayStatic;
using md_audio::MdFloat;

DelayStatic::DelayStatic(memory::Poolable& pool, std::size_t max_delay) :
    m_buffer(pool, max_delay),
    m_reader(m_buffer, max_delay - 1),
    m_writer(m_buffer, max_delay - 1),
    m_max_delay(static_cast<MdFloat>(max_delay))
{
    m_buffer.initialise();

    set_delay(static_cast<MdFloat>(1));
}

DelayStatic::DelayStatic(memory::Poolable& pool, std::size_t max_delay, MdFloat delay) :
    m_buffer(pool, max_delay),
    m_reader(m_buffer, max_delay - 1),
    m_writer(m_buffer, max_delay - 1),
    m_max_delay(static_cast<MdFloat>(max_delay))
{
    m_buffer.initialise();

    set_delay(delay);
}

MdFloat DelayStatic::perform(MdFloat in) noexcept {
    auto z = m_reader.read(m_writer, m_delay);

    m_writer.write(in);

    return z;
}
