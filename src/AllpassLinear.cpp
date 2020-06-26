#include "AllpassLinear.hpp"

using md_audio::AllpassLinear;
using md_audio::MdFloat;

AllpassLinear::AllpassLinear(memory::Poolable& pool, MdFloat max_delay) :
    m_max_delay(static_cast<std::uint32_t>(sample_rate * max_delay) + 2),
    m_buffer(pool, m_max_delay),
    m_reader(m_buffer, m_max_delay - 1),
    m_writer(m_buffer, m_max_delay - 1)
{
    m_buffer.initialise();

    set_delay(static_cast<MdFloat>(1));
}

AllpassLinear::AllpassLinear(memory::Poolable& pool, MdFloat max_delay, MdFloat delay) :
    m_max_delay(static_cast<std::uint32_t>(sample_rate * max_delay) + 2),
    m_buffer(pool, m_max_delay),
    m_reader(m_buffer, m_max_delay - 1),
    m_writer(m_buffer, m_max_delay - 1)
{
    m_buffer.initialise();

    set_delay(delay);
}

AllpassLinear::AllpassLinear(
    memory::Poolable& pool,
    MdFloat max_delay,
    MdFloat delay,
    MdFloat gain
) :
    m_max_delay(static_cast<std::uint32_t>(sample_rate * max_delay) + 2),
    m_buffer(pool, m_max_delay),
    m_reader(m_buffer, m_max_delay - 1),
    m_writer(m_buffer, m_max_delay - 1)
{
    m_buffer.initialise();

    set_delay(delay);
    set_gain(gain);
}

MdFloat AllpassLinear::perform(MdFloat in) noexcept {
    auto sd = m_reader.read(m_writer, m_delay, m_frac);
    auto s = in + m_gain * sd;

    m_writer.write(s);

    return sd - m_gain * s;
}
