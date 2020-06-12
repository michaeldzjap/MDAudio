#include "DelayCubic.hpp"

using md_audio::DelayCubic;
using md_audio::MdFloat;

DelayCubic::DelayCubic(memory::Poolable& pool, std::size_t max_delay) :
    m_buffer(pool, max_delay),
    m_reader(m_buffer, max_delay - 1),
    m_writer(m_buffer, max_delay - 1),
    m_max_delay(static_cast<MdFloat>(max_delay - 2))
{
    m_buffer.initialise();

    set_delay(static_cast<MdFloat>(1));
}

DelayCubic::DelayCubic(memory::Poolable& pool, std::size_t max_delay, MdFloat delay) :
    m_buffer(pool, max_delay),
    m_reader(m_buffer, max_delay - 1),
    m_writer(m_buffer, max_delay - 1),
    m_max_delay(static_cast<MdFloat>(max_delay - 2))
{
    m_buffer.initialise();

    set_delay(delay);
}

MdFloat DelayCubic::perform(MdFloat in) noexcept {
    auto z = m_reader.read(m_writer, m_delay, m_frac);

    m_writer.write(in);

    return z;
}
