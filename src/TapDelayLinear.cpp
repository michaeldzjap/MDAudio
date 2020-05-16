#include "TapDelayLinear.hpp"

using md_audio::MdFloat;
using md_audio::TapDelayLinear;

TapDelayLinear::TapDelayLinear(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, std::size_t taps) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay - static_cast<MdFloat>(1)),
    m_taps(taps),
    m_delay(new std::uint32_t[m_taps]),
    m_frac(new MdFloat[m_taps])
{}

TapDelayLinear::TapDelayLinear(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay,
    const MdFloat* delay, std::size_t taps) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay - static_cast<MdFloat>(1)),
    m_taps(taps),
    m_delay(new std::uint32_t[m_taps]),
    m_frac(new MdFloat[m_taps])
{
    set_delay(delay);
}

void TapDelayLinear::initialise() {
    m_buffer.initialise();
}

void TapDelayLinear::set_delay(const MdFloat* delay) noexcept {
    for (auto i = 0; i < m_taps; ++i) set_delay(i, delay[i]);
}

MdFloat* TapDelayLinear::perform(MdFloat in, MdFloat* out, std::size_t) noexcept {
    m_writer.write(in);

    for (auto i = 0; i < m_taps; ++i)
        out[i] = m_reader.read(m_writer, m_delay[i], m_frac[i]);

    m_writer.increment();

    return out;
}

void TapDelayLinear::write(MdFloat in) noexcept {
    m_writer.write(in);
    m_writer.increment();
}

MdFloat TapDelayLinear::read(std::size_t index) noexcept {
    return m_reader.read(m_writer, m_delay[index], m_frac[index]);
}

TapDelayLinear::~TapDelayLinear() {
    delete[] m_delay;
    delete[] m_frac;
}
