#include "AllpassStatic.hpp"

using md_audio::AllpassStatic;
using md_audio::MdFloat;

AllpassStatic::AllpassStatic(memory::Poolable& pool, MdFloat max_delay) :
    m_max_delay(utility::ceil(sample_rate * max_delay)),
    m_buffer(pool, m_max_delay),
    m_reader(m_buffer, m_max_delay - 1),
    m_writer(m_buffer, m_max_delay - 1)
{
    m_buffer.initialise();

    set_delay(static_cast<MdFloat>(1));
}

AllpassStatic::AllpassStatic(memory::Poolable& pool, MdFloat max_delay, MdFloat delay) :
    m_max_delay(utility::ceil(sample_rate * max_delay)),
    m_buffer(pool, m_max_delay),
    m_reader(m_buffer, m_max_delay - 1),
    m_writer(m_buffer, m_max_delay - 1)
{
    m_buffer.initialise();

    set_delay(delay);
}

AllpassStatic::AllpassStatic(
    memory::Poolable& pool,
    MdFloat max_delay,
    MdFloat delay,
    MdFloat gain
) :
    m_max_delay(utility::ceil(sample_rate * max_delay)),
    m_buffer(pool, m_max_delay),
    m_reader(m_buffer, m_max_delay - 1),
    m_writer(m_buffer, m_max_delay - 1)
{
    m_buffer.initialise();

    set_delay(delay);
    set_gain(gain);
}

MdFloat AllpassStatic::perform(MdFloat in) noexcept {
    auto sd = m_reader.read(m_writer, m_delay);
    auto s = in + m_gain * sd;

    m_writer.write(s);

    return sd - m_gain * s;
}
