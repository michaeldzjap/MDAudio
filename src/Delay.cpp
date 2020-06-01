#include "Delay.hpp"

using md_audio::Delay;
using md_audio::MdFloat;

Delay::Delay(
    memory::Poolable& pool,
    std::size_t max_delay,
    InterpolationType interpolation_type
) :
    m_buffer(pool, max_delay),
    m_reader(m_buffer, max_delay - 1),
    m_reader_linear(m_buffer, max_delay - 1),
    m_reader_cubic(m_buffer, max_delay - 1),
    m_writer(m_buffer, max_delay - 1)
{
    initialise(max_delay, static_cast<MdFloat>(1), interpolation_type);
}

Delay::Delay(
    memory::Poolable& pool,
    std::size_t max_delay,
    MdFloat delay,
    InterpolationType interpolation_type
) :
    m_buffer(pool, max_delay),
    m_reader(m_buffer, max_delay - 1),
    m_reader_linear(m_buffer, max_delay - 1),
    m_reader_cubic(m_buffer, max_delay - 1),
    m_writer(m_buffer, max_delay - 1)
{
    initialise(max_delay, delay, interpolation_type);
}

void Delay::initialise(std::size_t max_delay, MdFloat delay, InterpolationType interpolation_type) noexcept {
    m_buffer.initialise();

    if (interpolation_type == InterpolationType::none) {
        Delay::perform_function = &Delay::perform_static;
        m_max_delay = max_delay;
    } else if (interpolation_type == InterpolationType::linear) {
        Delay::perform_function = &Delay::perform_linear;
        m_max_delay = max_delay - 1;
    } else {
        Delay::perform_function = &Delay::perform_cubic;
        m_max_delay = max_delay - 2;
    }

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
