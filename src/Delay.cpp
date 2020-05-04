#include "Delay.hpp"

using md_audio::Delay;
using md_audio::MdFloat;

Delay::Delay(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay,
    InterpolationType interpolation_type) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer),
    m_reader_linear(m_buffer),
    m_reader_cubic(m_buffer),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay)
{
    initialise(static_cast<MdFloat>(1), interpolation_type);
}

Delay::Delay(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, MdFloat delay,
    InterpolationType interpolation_type) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer),
    m_reader_linear(m_buffer),
    m_reader_cubic(m_buffer),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay)
{
    initialise(delay, interpolation_type);
}

void Delay::initialise() {
    m_buffer.initialise();
}

void Delay::initialise(MdFloat delay, InterpolationType interpolation_type) noexcept {
    set_delay(delay);

    if (interpolation_type == InterpolationType::none)
        Delay::perform_function = &Delay::perform_static;
    else if (interpolation_type == InterpolationType::linear)
        Delay::perform_function = &Delay::perform_linear;
    else
        Delay::perform_function = &Delay::perform_cubic;
}

MdFloat Delay::perform(MdFloat in) noexcept {
    return (this->*perform_function)(in);
}

MdFloat Delay::perform_static(MdFloat in) noexcept {
    m_writer.write(in);

    auto z = m_reader.read(m_writer, m_delay);

    m_writer.increment();

    return z;
}

MdFloat Delay::perform_linear(MdFloat in) noexcept {
    m_writer.write(in);

    auto z = m_reader_linear.read(m_writer, m_delay, m_frac);

    m_writer.increment();

    return z;
}

MdFloat Delay::perform_cubic(MdFloat in) noexcept {
    m_writer.write(in);

    auto z = m_reader_cubic.read(m_writer, m_delay, m_frac);

    m_writer.increment();

    return z;
}
