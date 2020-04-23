#include "Delay.hpp"

using md_audio::Delay;
using md_audio::MdFloat;

Delay::Delay(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay)
{
    set_delay(static_cast<MdFloat>(1));
}

Delay::Delay(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, MdFloat delay) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay)
{
    set_delay(delay);
}

void Delay::initialise() {
    m_buffer.initialise();
}

MdFloat Delay::perform(MdFloat in) noexcept {
    m_writer.write(in);

    auto z = m_reader.read(m_writer, m_delay);

    m_writer.increment();

    return z;
}
