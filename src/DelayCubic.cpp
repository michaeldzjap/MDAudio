#include "DelayCubic.hpp"

using md_audio::DelayCubic;
using md_audio::MdFloat;

DelayCubic::DelayCubic(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay - static_cast<MdFloat>(2))
{
    set_delay(static_cast<MdFloat>(1));
}

DelayCubic::DelayCubic(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, MdFloat delay) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay - static_cast<MdFloat>(2))
{
    set_delay(delay);
}

void DelayCubic::initialise() {
    m_buffer.initialise();
}

void DelayCubic::set_delay(MdFloat delay) noexcept {
    delay = utility::clip(delay, static_cast<MdFloat>(1), m_max_delay);

    m_delay = static_cast<std::uint32_t>(delay);
    m_frac = delay - static_cast<MdFloat>(m_delay);
}

MdFloat DelayCubic::perform(MdFloat in) noexcept {
    m_writer.write(in);

    auto z = m_reader.read(m_writer, m_delay, m_frac);

    m_writer.increment();

    return z;
}
