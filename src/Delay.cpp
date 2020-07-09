#include "Delay.hpp"

using md_audio::Delay;
using md_audio::MdFloat;

Delay::Delay(
    memory::Poolable& pool,
    MdFloat max_delay,
    InterpolationType interpolation_type
) :
    m_max_delay(compute_max_delay(max_delay, interpolation_type)),
    m_buffer(pool, m_max_delay),
    m_reader(m_buffer, m_max_delay - 1),
    m_reader_linear(m_buffer, m_max_delay - 1),
    m_reader_cubic(m_buffer, m_max_delay - 1),
    m_writer(m_buffer, m_max_delay - 1)
{
    initialise(static_cast<MdFloat>(1), interpolation_type);
}

Delay::Delay(
    memory::Poolable& pool,
    MdFloat max_delay,
    MdFloat delay,
    InterpolationType interpolation_type
) :
    m_max_delay(compute_max_delay(max_delay, interpolation_type)),
    m_buffer(pool, m_max_delay),
    m_reader(m_buffer, m_max_delay - 1),
    m_reader_linear(m_buffer, m_max_delay - 1),
    m_reader_cubic(m_buffer, m_max_delay - 1),
    m_writer(m_buffer, m_max_delay - 1)
{
    initialise(delay, interpolation_type);
}

void Delay::initialise(
    MdFloat delay,
    InterpolationType interpolation_type
) noexcept {
    if (interpolation_type == InterpolationType::none)
        Delay::perform_function = &Delay::perform_static;
    else if (interpolation_type == InterpolationType::linear)
        Delay::perform_function = &Delay::perform_linear;
    else
        Delay::perform_function = &Delay::perform_cubic;

    set_delay(delay);
}

MdFloat Delay::perform(MdFloat in) noexcept {
    return (this->*perform_function)(in);
}

MdFloat Delay::perform_static(MdFloat in) noexcept {
    auto z = m_reader.read(m_writer, m_delay);

    m_writer.write(in);

    return z;
}

MdFloat Delay::perform_linear(MdFloat in) noexcept {
    auto z = m_reader_linear.read(m_writer, m_delay, m_frac);

    m_writer.write(in);

    return z;
}

MdFloat Delay::perform_cubic(MdFloat in) noexcept {
    auto z = m_reader_cubic.read(m_writer, m_delay, m_frac);

    m_writer.write(in);

    return z;
}

std::uint32_t Delay::compute_max_delay(
    MdFloat max_delay,
    InterpolationType interpolation_type
) noexcept {
    switch (interpolation_type) {
        case InterpolationType::none:
            return utility::ceil(sample_rate * max_delay);
        case InterpolationType::linear:
            return utility::ceil(sample_rate * max_delay) + 1;
        default:
            return utility::ceil(sample_rate * max_delay) + 2;
    }
}
