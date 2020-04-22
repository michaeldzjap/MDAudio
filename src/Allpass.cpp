#include "Allpass.hpp"
#include "utility.hpp"

using md_audio::Allpass;
using md_audio::MdFloat;

Allpass::Allpass(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay)
{
    set_delay(static_cast<MdFloat>(1));
}

Allpass::Allpass(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, MdFloat delay) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay)
{
    set_delay(delay);
}

Allpass::Allpass(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, MdFloat delay, MdFloat gain) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay)
{
    set_delay(delay);
    set_gain(gain);
}

void Allpass::initialise() {
    m_buffer.initialise();
}

void Allpass::set_delay(MdFloat delay) noexcept {
    delay = utility::clip(delay, static_cast<MdFloat>(1), m_max_delay);

    m_delay = static_cast<std::uint32_t>(delay);
}

void Allpass::set_gain(MdFloat gain) noexcept {
    m_gain = utility::clip(gain, static_cast<MdFloat>(0), static_cast<MdFloat>(1));
}

MdFloat Allpass::perform(MdFloat in) noexcept {
    auto sd = m_reader.read(m_writer, m_delay);
    auto s = in + m_gain * sd;

    m_writer.write(s);
    m_writer.increment();

    return sd - m_gain * s;
}
