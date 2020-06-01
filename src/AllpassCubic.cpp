#include "AllpassCubic.hpp"

using md_audio::AllpassCubic;
using md_audio::MdFloat;

AllpassCubic::AllpassCubic(memory::Poolable& pool, size_t max_delay) :
    m_buffer(pool, max_delay),
    m_reader(m_buffer, max_delay - 1),
    m_writer(m_buffer, max_delay - 1),
    m_max_delay(static_cast<MdFloat>(max_delay - 2))
{
    set_delay(static_cast<MdFloat>(1));
}

AllpassCubic::AllpassCubic(memory::Poolable& pool, size_t max_delay, MdFloat delay) :
    m_buffer(pool, max_delay),
    m_reader(m_buffer, max_delay - 1),
    m_writer(m_buffer, max_delay - 1),
    m_max_delay(static_cast<MdFloat>(max_delay - 2))
{
    set_delay(delay);
}

AllpassCubic::AllpassCubic(memory::Poolable& pool, size_t max_delay, MdFloat delay, MdFloat gain) :
    m_buffer(pool, max_delay),
    m_reader(m_buffer, max_delay - 1),
    m_writer(m_buffer, max_delay - 1),
    m_max_delay(static_cast<MdFloat>(max_delay - 2))
{
    set_delay(delay);
    set_gain(gain);
}

void AllpassCubic::initialise() {
    m_buffer.initialise();
}

MdFloat AllpassCubic::perform(MdFloat in) noexcept {
    auto sd = m_reader.read(m_writer, m_delay, m_frac);
    auto s = in + m_gain * sd;

    m_writer.write(s);

    return sd - m_gain * s;
}
