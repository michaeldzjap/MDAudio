#ifndef MD_AUDIO_READER_HPP
#define MD_AUDIO_READER_HPP

#include <cstddef>
#include "Buffer.hpp"

using md_audio::Buffer;

namespace md_audio {

    template <class Allocator>
    class Reader {
    public:
        explicit Reader(Buffer<Allocator>& buffer) :
            m_buffer(buffer),
            m_mask(m_buffer.m_size - 1)
        {}

        double read(std::size_t read_index) const noexcept {
            return m_buffer[read_index & m_mask];
        }

    private:
        Buffer<Allocator>& m_buffer;
        std::size_t m_mask;
    };

}

#endif /* MD_AUDIO_READER_HPP */
