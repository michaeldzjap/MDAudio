#include "TapDelay.hpp"

using md_audio::MdFloat;
using md_audio::TapDelay;

TapDelay::TapDelay(
    memory::Poolable& pool,
    MdFloat max_delay,
    std::size_t taps,
    InterpolationType interpolation_type
) :
    m_max_delay(compute_max_delay(max_delay, interpolation_type)),
    m_taps(taps),
    m_pool(pool),
    m_buffer(pool, m_max_delay),
    m_reader(m_buffer, m_max_delay - 1),
    m_reader_linear(m_buffer, m_max_delay - 1),
    m_reader_cubic(m_buffer, m_max_delay - 1),
    m_writer(m_buffer, m_max_delay - 1)
{
    initialise(interpolation_type);
}

void TapDelay::initialise(InterpolationType interpolation_type) {
    m_buffer.initialise();

    m_delay = static_cast<std::uint32_t*>(m_pool.allocate(m_taps * sizeof(std::uint32_t)));
    m_frac = static_cast<MdFloat*>(m_pool.allocate(m_taps * sizeof(MdFloat)));

    if (interpolation_type == InterpolationType::none) {
        perform_function = &TapDelay::perform_static;
        read_function = &TapDelay::read_static;
     } else if (interpolation_type == InterpolationType::linear) {
        perform_function = &TapDelay::perform_linear;
        read_function = &TapDelay::read_linear;
    } else {
        perform_function = &TapDelay::perform_cubic;
        read_function = &TapDelay::read_cubic;
    }

    for (std::uint32_t i = 0; i < m_taps; ++i)
        set_delay(i, static_cast<MdFloat>(1));
}

void TapDelay::set_delay(const MdFloat* delay) noexcept {
    for (std::uint32_t i = 0; i < m_taps; ++i) set_delay(i, delay[i]);
}

MdFloat* TapDelay::perform(MdFloat in, MdFloat* out, std::size_t n) noexcept {
    return (this->*perform_function)(in, out, n);
}

MdFloat* TapDelay::perform_static(MdFloat in, MdFloat* out, std::size_t) noexcept {
    for (std::uint32_t i = 0; i < m_taps; ++i)
        out[i] = m_reader.read(m_writer, m_delay[i]);

    m_writer.write(in);

    return out;
}

MdFloat* TapDelay::perform_linear(MdFloat in, MdFloat* out, std::size_t) noexcept {
    for (std::uint32_t i = 0; i < m_taps; ++i)
        out[i] = m_reader_linear.read(m_writer, m_delay[i], m_frac[i]);

    m_writer.write(in);

    return out;
}

MdFloat* TapDelay::perform_cubic(MdFloat in, MdFloat* out, std::size_t) noexcept {
    for (std::uint32_t i = 0; i < m_taps; ++i)
        out[i] = m_reader_cubic.read(m_writer, m_delay[i], m_frac[i]);

    m_writer.write(in);

    return out;
}

void TapDelay::write(MdFloat in) noexcept {
    m_writer.write(in);
}

MdFloat TapDelay::read(std::size_t index) noexcept {
    return (this->*read_function)(index);
}

MdFloat TapDelay::read_static(std::size_t index) noexcept {
    return m_reader.read(m_writer, m_delay[index]);
}

MdFloat TapDelay::read_linear(std::size_t index) noexcept {
    return m_reader_linear.read(m_writer, m_delay[index], m_frac[index]);
}

MdFloat TapDelay::read_cubic(std::size_t index) noexcept {
    return m_reader_cubic.read(m_writer, m_delay[index], m_frac[index]);
}

std::uint32_t TapDelay::compute_max_delay(
    MdFloat max_delay,
    InterpolationType interpolation_type
) noexcept {
    switch (interpolation_type) {
        case InterpolationType::none:
            return static_cast<std::uint32_t>(sample_rate * max_delay) + 1;
        case InterpolationType::linear:
            return static_cast<std::uint32_t>(sample_rate * max_delay) + 2;
        default:
            return static_cast<std::uint32_t>(sample_rate * max_delay) + 3;
    }
}

TapDelay::~TapDelay() {
    if (m_delay) m_pool.deallocate(m_delay);
    if (m_frac) m_pool.deallocate(m_frac);
}
