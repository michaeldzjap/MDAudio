#include "ReaderLinear.hpp"
#include "utility.hpp"

using md_audio::MdFloat;
using md_audio::ReaderLinear;
using md_audio::Writer;

ReaderLinear::ReaderLinear(Buffer& buffer, Writer& writer) :
    m_buffer(buffer),
    m_lower_bound(writer.m_lower_bound),
    m_upper_bound(writer.m_upper_bound)
{}

ReaderLinear::ReaderLinear(Buffer& buffer, std::uint32_t upper_bound) :
    m_buffer(buffer),
    m_upper_bound(upper_bound)
{}

ReaderLinear::ReaderLinear(Buffer& buffer, std::uint32_t lower_bound, std::uint32_t upper_bound) :
    m_buffer(buffer),
    m_lower_bound(lower_bound),
    m_upper_bound(upper_bound)
{}

MdFloat ReaderLinear::read(Writer& writer, std::uint32_t offset, MdFloat frac) noexcept {
    // Get the correct read positions into the buffer
    auto phase_a = utility::wrap(writer.m_write_index - offset, m_lower_bound, m_upper_bound);
    auto phase_b = utility::wrap(phase_a - 1, 0, m_upper_bound);

    auto d1 = m_buffer[phase_a];
    auto d2 = m_buffer[phase_b];

    return utility::linear_interp(frac, d1, d2);
}
