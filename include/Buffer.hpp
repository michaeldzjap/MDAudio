#ifndef MD_AUDIO_BUFFER_HPP
#define MD_AUDIO_BUFFER_HPP

#include "types.hpp"
#include "utility.hpp"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <new>

namespace md_audio {

    template <typename Allocator>
    class Buffer {
    public:
        explicit Buffer(Allocator&, std::uint32_t);

        void initialise();

        MdFloat& operator[] (std::size_t) noexcept;

        const MdFloat& operator[] (std::size_t) const noexcept;

        ~Buffer();

    protected:
        MdFloat* m_memory = nullptr;
        const std::uint32_t m_size;

    private:
        Allocator& m_allocator;
    };

    template <typename Allocator>
    Buffer<Allocator>::Buffer(Allocator& allocator, std::uint32_t size) :
        m_allocator(allocator),
        m_size(size)
    {}

    template <typename Allocator>
    void Buffer<Allocator>::initialise() {
        m_memory = m_allocator.allocate(m_size);

        if (!m_memory)
            throw std::bad_alloc();

        std::memset(m_memory, 0, m_size * sizeof(MdFloat));
    }

    template <typename Allocator>
    MdFloat& Buffer<Allocator>::operator[] (std::size_t index) noexcept {
        assert(index >= 0 && index < m_size);

        return m_memory[index];
    }

    template <typename Allocator>
    const MdFloat& Buffer<Allocator>::operator[] (std::size_t index) const noexcept {
        assert(index >= 0 && index < m_size);

        return m_memory[index];
    }

    template <typename Allocator>
    Buffer<Allocator>::~Buffer() {
        if (m_memory)
            m_allocator.deallocate(m_memory, m_size);
    }

}

#endif /* MD_AUDIO_BUFFER_HPP */
