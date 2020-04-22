#include "Reader.hpp"
#include "utility.hpp"

using md_audio::MdFloat;
using md_audio::Reader;
using md_audio::Writer;

Reader::Reader(Buffer& buffer) : m_buffer(buffer) {}

MdFloat Reader::read(Writer& writer, std::uint32_t offset) noexcept {
    // Get the correct read position into the buffer
    auto phase = utility::wrap(
        writer.m_write_index - offset, writer.m_lower_bound, writer.m_upper_bound
    );

    return m_buffer[phase];
}
