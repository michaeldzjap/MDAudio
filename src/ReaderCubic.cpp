#include "ReaderCubic.hpp"
#include "utility.hpp"

using md_audio::MdFloat;
using md_audio::ReaderCubic;
using md_audio::Writer;

ReaderCubic::ReaderCubic(Buffer& buffer) : m_buffer(buffer) {}

MdFloat ReaderCubic::read(Writer& writer, std::uint32_t offset, MdFloat frac) noexcept {
    // Get the correct read positions into the buffer
    auto phase_1 = utility::wrap(
        writer.m_write_index - offset, writer.m_lower_bound, writer.m_upper_bound
    );
    auto phase_2 = utility::wrap(phase_1 - 1, 0, writer.m_upper_bound);
    auto phase_3 = utility::wrap(phase_1 - 2, 0, writer.m_upper_bound);
    auto phase_0 = utility::wrap(phase_1 + 1, 0, writer.m_upper_bound);

    auto d0 = m_buffer[phase_0];
    auto d1 = m_buffer[phase_1];
    auto d2 = m_buffer[phase_2];
    auto d3 = m_buffer[phase_3];

    return utility::cubic_interp(frac, d0, d1, d2, d3);
}
