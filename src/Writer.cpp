#include "Writer.hpp"
#include "utility.hpp"

using md_audio::Buffer;
using md_audio::MdFloat;
using md_audio::Writer;

Writer::Writer(Buffer& buffer, std::uint32_t upper_bound) :
    m_buffer(buffer),
    m_upper_bound(upper_bound)
{}

Writer::Writer(Buffer& buffer, std::uint32_t lower_bound, std::uint32_t upper_bound) :
    m_buffer(buffer),
    m_lower_bound(lower_bound),
    m_upper_bound(upper_bound),
    m_write_index(m_lower_bound)
{}

void Writer::write(MdFloat in) noexcept {
    m_buffer[m_write_index] = in;
}

void Writer::increment() noexcept {
    m_write_index = utility::wrap(m_write_index + 1, m_lower_bound, m_upper_bound);
}
