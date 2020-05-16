#include "Normaliser.hpp"

using md_audio::MdFloat;
using md_audio::Normaliser;

Normaliser::Normaliser(memory::Allocatable<MdFloat*>& allocator, std::uint32_t duration) :
    m_buffer(allocator, duration * 3),
    m_reader_in(m_buffer, 0, duration - 1),
    m_reader_mid(m_buffer, duration, (duration << 1) - 1),
    m_reader_out(m_buffer, duration << 1, duration * 3 - 1),
    m_writer(m_buffer, duration * 3 - 1),
    m_slope_factor(static_cast<MdFloat>(1) / static_cast<MdFloat>(duration))
{
    set_amplitude(static_cast<MdFloat>(1));
}

Normaliser::Normaliser(memory::Allocatable<MdFloat*>& allocator, std::uint32_t duration, MdFloat amplitude) :
    m_buffer(allocator, duration * 3),
    m_reader_in(m_buffer, 0, duration - 1),
    m_reader_mid(m_buffer, duration, (duration << 1) - 1),
    m_reader_out(m_buffer, duration << 1, duration * 3 - 1),
    m_writer(m_buffer, duration * 3 - 1),
    m_slope_factor(static_cast<MdFloat>(1) / static_cast<MdFloat>(duration))
{
    set_amplitude(amplitude);
}

MdFloat Normaliser::perform(MdFloat) noexcept {
    //
}
