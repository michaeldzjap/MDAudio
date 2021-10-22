#ifndef MD_AUDIO_BUFFER_HPP
#define MD_AUDIO_BUFFER_HPP

#include <cstddef>
#include <cstring>
#include "types.hpp"

namespace md_audio {

    template <class Allocator>
    class Buffer {
    public:
        explicit Buffer(Allocator& allocator, std::size_t size) :
            m_allocator(allocator),
            m_size(size)
        {}

        bool initialise() noexcept {
            m_memory = m_allocator.allocate(m_size);

            if (!m_memory)
                return false;

            std::memset(m_memory, 0, m_size * sizeof(MdFloat));

            return true;
        }

        MdFloat& operator[] (std::size_t index) noexcept {
            return m_memory[index];
        }

        const MdFloat& operator[] (std::size_t index) const noexcept {
            return m_memory[index];
        }

        ~Buffer() {
            if (m_memory)
                m_allocator.deallocate(m_memory);
        }

    private:
        Allocator& m_allocator;
        const std::size_t m_size;
        MdFloat* m_memory = nullptr;

        template <class> friend class Reader;
        template <class> friend class ReaderCubic;
        template <class> friend class ReaderLinear;
        template <class> friend class Writer;
    };

}

#endif /* MD_AUDIO_BUFFER_HPP */
