#include "AllpassStatic.hpp"

using md_audio::AllpassStatic;
using md_audio::MdFloat;

AllpassStatic::AllpassStatic(memory::Poolable& pool, std::size_t max_delay) :
    m_buffer(pool, max_delay),
    m_reader(m_buffer, max_delay - 1),
    m_writer(m_buffer, max_delay - 1),
    m_max_delay(static_cast<MdFloat>(max_delay))
{
    set_delay(static_cast<MdFloat>(1));
}

AllpassStatic::AllpassStatic(memory::Poolable& pool, std::size_t max_delay, MdFloat delay) :
    m_buffer(pool, max_delay),
    m_reader(m_buffer, max_delay - 1),
    m_writer(m_buffer, max_delay - 1),
    m_max_delay(static_cast<MdFloat>(max_delay))
{
    set_delay(delay);
}

AllpassStatic::AllpassStatic(memory::Poolable& pool, std::size_t max_delay, MdFloat delay, MdFloat gain) :
    m_buffer(pool, max_delay),
    m_reader(m_buffer, max_delay - 1),
    m_writer(m_buffer, max_delay - 1),
    m_max_delay(static_cast<MdFloat>(max_delay))
{
    set_delay(delay);
    set_gain(gain);
}

void AllpassStatic::initialise() {
    m_buffer.initialise();
}

MdFloat AllpassStatic::perform(MdFloat in) noexcept {
    auto sd = m_reader.read(m_writer, m_delay);
    auto s = in + m_gain * sd;

    m_writer.write(s);

    return sd - m_gain * s;
}
