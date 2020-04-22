#include "ReaderLinear.hpp"
#include "utility.hpp"

using md_audio::MdFloat;
using md_audio::ReaderLinear;
using md_audio::Writer;

ReaderLinear::ReaderLinear(Buffer& buffer) : m_buffer(buffer) {}

MdFloat ReaderLinear::read(Writer& writer, std::uint32_t offset, MdFloat frac) noexcept {
    // Get the correct read positions into the buffer
    auto phase_a = utility::wrap(
        writer.m_write_index - offset, writer.m_lower_bound, writer.m_upper_bound
    );
    auto phase_b = utility::wrap(phase_a - 1, 0, writer.m_upper_bound);

    auto d1 = m_buffer[phase_a];
    auto d2 = m_buffer[phase_b];

    return utility::linear_interp(frac, d1, d2);
}
