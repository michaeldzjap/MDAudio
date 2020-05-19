#include "TapDelayStatic.hpp"

using md_audio::MdFloat;
using md_audio::TapDelayStatic;

TapDelayStatic::TapDelayStatic(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, std::size_t taps) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay),
    m_taps(taps),
    m_delay(new std::uint32_t[m_taps])
{}

TapDelayStatic::TapDelayStatic(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay,
    const MdFloat* delay, std::size_t taps) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay),
    m_taps(taps),
    m_delay(new std::uint32_t[m_taps])
{
    set_delay(delay);
}

void TapDelayStatic::initialise() {
    m_buffer.initialise();
}

void TapDelayStatic::set_delay(const MdFloat* delay) noexcept {
    for (auto i = 0; i < m_taps; ++i) set_delay(i, delay[i]);
}

MdFloat* TapDelayStatic::perform(MdFloat in, MdFloat* out, std::size_t) noexcept {
    m_writer.write(in);

    for (auto i = 0; i < m_taps; ++i)
        out[i] = m_reader.read(m_writer, m_delay[i]);

    return out;
}

void TapDelayStatic::write(MdFloat in) noexcept {
    m_writer.write(in);
}

MdFloat TapDelayStatic::read(std::size_t index) noexcept {
    return m_reader.read(m_writer, m_delay[index]);
}

TapDelayStatic::~TapDelayStatic() {
    delete[] m_delay;
}
