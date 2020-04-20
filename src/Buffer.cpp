#include "Buffer.hpp"

using md_audio::Buffer;
using md_audio::MdFloat;

Buffer::Buffer(memory::Allocatable<MdFloat*>& allocator, std::uint32_t size) :
    m_allocator(allocator),
    m_size(size)
{}

void Buffer::initialise() {
    m_memory = m_allocator.allocate(m_size);

    if (!m_memory)
        throw std::bad_alloc();

    std::memset(m_memory, 0, m_size * sizeof(MdFloat));
}

MdFloat& Buffer::operator[] (std::size_t index) noexcept {
    assert(index >= 0 && index < m_size);

    return m_memory[index];
}

const MdFloat& Buffer::operator[] (std::size_t index) const noexcept {
    assert(index >= 0 && index < m_size);

    return m_memory[index];
}

Buffer::~Buffer() {
    if (m_memory)
        m_allocator.deallocate(m_memory, m_size);
}
