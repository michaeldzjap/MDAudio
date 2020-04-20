#include "Writer.hpp"

using md_audio::Writer;
using md_audio::MdFloat;

Writer::Writer(memory::Allocatable<MdFloat*>& allocator, std::uint32_t upper_bound) :
    m_buffer(allocator, upper_bound),
    m_upper_bound_1(upper_bound - 1)
{}

void Writer::initialise() {
    m_buffer.initialise();
}

void Writer::write(MdFloat in) noexcept {
    m_buffer[m_write_index] = in;
}

void Writer::increment() noexcept {
    m_write_index = utility::wrap(m_write_index + 1, 0, m_upper_bound_1);
}

Writer::~Writer() {}
