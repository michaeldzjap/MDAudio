#include "Buffer.hpp"
#include <cstring>

using md_audio::Buffer;
using md_audio::MdFloat;

Buffer::Buffer(memory::Poolable& pool, std::size_t size) :
    m_pool(pool),
    m_size(size)
{
    initialise();
}

void Buffer::initialise() {
    m_memory = static_cast<MdFloat*>(m_pool.allocate(m_size * sizeof(MdFloat)));

    std::memset(m_memory, 0, m_size * sizeof(MdFloat));
}

MdFloat& Buffer::operator[] (std::size_t index) noexcept {
    return m_memory[index];
}

const MdFloat& Buffer::operator[] (std::size_t index) const noexcept {
    return m_memory[index];
}

Buffer::~Buffer() {
    if (m_memory) m_pool.deallocate(m_memory);
}
