#include "Buffer.hpp"
#include "utility.hpp"
#include <cassert>
#include <cstring>
#include <new>

using md_audio::Buffer;
using md_audio::MdFloat;

Buffer::Buffer(memory::Poolable& pool, std::size_t size) :
    m_pool(pool),
    m_size(size)
{}

void Buffer::initialise() {
    auto memory = m_pool.allocate(m_size * sizeof(MdFloat));

    if (!memory)
        throw std::bad_alloc();

    m_memory = static_cast<MdFloat*>(memory);

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
        m_pool.deallocate(m_memory);
}
