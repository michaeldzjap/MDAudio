#include "ReaderCubic.hpp"
#include "utility.hpp"

using md_audio::MdFloat;
using md_audio::ReaderCubic;
using md_audio::Writer;

ReaderCubic::ReaderCubic(Buffer& buffer, Writer& writer) :
    m_buffer(buffer),
    m_lower_bound(writer.m_lower_bound),
    m_upper_bound(writer.m_upper_bound)
{}

ReaderCubic::ReaderCubic(Buffer& buffer, std::size_t upper_bound) :
    m_buffer(buffer),
    m_upper_bound(upper_bound)
{}

ReaderCubic::ReaderCubic(Buffer& buffer, std::size_t lower_bound, std::size_t upper_bound) :
    m_buffer(buffer),
    m_lower_bound(lower_bound),
    m_upper_bound(upper_bound)
{}

MdFloat ReaderCubic::read(Writer& writer, std::size_t offset, MdFloat frac) noexcept {
    // Get the correct read positions into the buffer
    auto phase_1 = utility::wrap(writer.m_write_index - offset, m_lower_bound, m_upper_bound);
    auto phase_2 = utility::wrap(phase_1 - 1, 0, m_upper_bound);
    auto phase_3 = utility::wrap(phase_1 - 2, 0, m_upper_bound);
    auto phase_0 = utility::wrap(phase_1 + 1, 0, m_upper_bound);

    auto d0 = m_buffer[phase_0];
    auto d1 = m_buffer[phase_1];
    auto d2 = m_buffer[phase_2];
    auto d3 = m_buffer[phase_3];

    return utility::cubic_interp(frac, d0, d1, d2, d3);
}
