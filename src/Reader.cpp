#include "Reader.hpp"
#include "utility.hpp"

using md_audio::MdFloat;
using md_audio::Reader;
using md_audio::Writer;

Reader::Reader(Buffer& buffer, Writer& writer) :
    m_buffer(buffer),
    m_lower_bound(writer.m_lower_bound),
    m_upper_bound(writer.m_upper_bound)
{}

Reader::Reader(Buffer& buffer, std::size_t upper_bound) :
    m_buffer(buffer),
    m_upper_bound(upper_bound)
{}

Reader::Reader(Buffer& buffer, std::size_t lower_bound, std::size_t upper_bound) :
    m_buffer(buffer),
    m_lower_bound(lower_bound),
    m_upper_bound(upper_bound)
{}

MdFloat Reader::read(Writer& writer, std::size_t offset) const noexcept {
    // Get the correct read position into the buffer
    auto phase = utility::wrap(writer.m_write_index - offset, m_lower_bound, m_upper_bound);

    return m_buffer[phase];
}
