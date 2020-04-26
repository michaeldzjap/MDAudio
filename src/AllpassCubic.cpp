#include "AllpassCubic.hpp"

using md_audio::AllpassCubic;
using md_audio::MdFloat;

AllpassCubic::AllpassCubic(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay - static_cast<MdFloat>(2))
{
    set_delay(static_cast<MdFloat>(1));
}

AllpassCubic::AllpassCubic(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, MdFloat delay) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay - static_cast<MdFloat>(1))
{
    set_delay(delay);
}

AllpassCubic::AllpassCubic(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, MdFloat delay, MdFloat gain) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay - static_cast<MdFloat>(1))
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
    m_writer.increment();

    return sd - m_gain * s;
}