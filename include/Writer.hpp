#ifndef MD_AUDIO_WRITER_HPP
#define MD_AUDIO_WRITER_HPP

#include "Buffer.hpp"

namespace md_audio {

    template <class Allocator>
    class Writer {
    public:
        explicit Writer(Buffer<Allocator>& buffer) :
            m_buffer(buffer),
            m_mask(buffer.m_size - 1),
            m_write_index(0)
        {}

        void write(double in) noexcept {
            m_buffer[m_write_index] = in;

            m_write_index = (m_write_index + 1) & m_mask;
        }

    private:
        Buffer<Allocator>& m_buffer;
        std::size_t m_mask;
        std::size_t m_write_index;

        template <class> friend class DelayCubic;
        template <class> friend class DelayLinear;
        template <class> friend class DelayStatic;
    };

}

#endif /* MD_AUDIO_WRITER_HPP */
