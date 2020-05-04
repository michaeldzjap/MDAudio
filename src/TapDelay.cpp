#include "TapDelay.hpp"

using md_audio::MdFloat;
using md_audio::TapDelay;

TapDelay::TapDelay(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, std::size_t taps,
    InterpolationType interpolation_type) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer),
    m_reader_linear(m_buffer),
    m_reader_cubic(m_buffer),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay - static_cast<MdFloat>(2)),
    m_taps(taps),
    m_delay(new std::uint32_t[m_taps]),
    m_frac(new MdFloat[m_taps])
{
    MdFloat* delay = new MdFloat[m_taps]{static_cast<MdFloat>(1)};

    initialise(delay, interpolation_type);

    delete[] delay;
}

TapDelay::TapDelay(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay,
    const MdFloat* delay, std::size_t taps, InterpolationType interpolation_type) :
    m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer),
    m_reader_linear(m_buffer),
    m_reader_cubic(m_buffer),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay - static_cast<MdFloat>(2)),
    m_taps(taps),
    m_delay(new std::uint32_t[m_taps]),
    m_frac(new MdFloat[m_taps])
{
    initialise(delay, interpolation_type);
}

void TapDelay::initialise() {
    m_buffer.initialise();
}

void TapDelay::initialise(const MdFloat* delay, InterpolationType interpolation_type) noexcept {
    set_delay(delay);

    if (interpolation_type == InterpolationType::none) {
        TapDelay::perform_function = &TapDelay::perform_static;
        TapDelay::read_function = &TapDelay::read_static;
    } else if (interpolation_type == InterpolationType::linear) {
        TapDelay::perform_function = &TapDelay::perform_linear;
        TapDelay::read_function = &TapDelay::read_linear;
    } else {
        TapDelay::perform_function = &TapDelay::perform_cubic;
        TapDelay::read_function = &TapDelay::read_cubic;
    }
}

void TapDelay::set_delay(const MdFloat* delay) noexcept {
    for (auto i = 0; i < m_taps; i++) set_delay(i, delay[i]);
}

MdFloat* TapDelay::perform(MdFloat in, MdFloat* out, std::size_t n) noexcept {
    return (this->*perform_function)(in, out, n);
}

MdFloat* TapDelay::perform_static(MdFloat in, MdFloat* out, std::size_t) noexcept {
    m_writer.write(in);

    for (auto i = 0; i < m_taps; i++)
        out[i] = m_reader.read(m_writer, m_delay[i]);

    m_writer.increment();

    return out;
}

MdFloat* TapDelay::perform_linear(MdFloat in, MdFloat* out, std::size_t) noexcept {
    m_writer.write(in);

    for (auto i = 0; i < m_taps; i++)
        out[i] = m_reader_linear.read(m_writer, m_delay[i], m_frac[i]);

    m_writer.increment();

    return out;
}

MdFloat* TapDelay::perform_cubic(MdFloat in, MdFloat* out, std::size_t) noexcept {
    m_writer.write(in);

    for (auto i = 0; i < m_taps; i++)
        out[i] = m_reader_cubic.read(m_writer, m_delay[i], m_frac[i]);

    m_writer.increment();

    return out;
}

void TapDelay::write(MdFloat in) noexcept {
    m_writer.write(in);
    m_writer.increment();
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

TapDelay::~TapDelay() {
    delete[] m_delay;
    delete[] m_frac;
}
