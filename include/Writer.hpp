#ifndef MD_AUDIO_WRITER_HPP
#define MD_AUDIO_WRITER_HPP

#include <cstddef>
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

        template <class, class> friend class AllpassInterpolated;
        template <class, class> friend class AllpassUninterpolated;
        template <class, class> friend class DelayInterpolated;
        template <class, class> friend class DelayUninterpolated;
        template <class, class> friend class TapInterpolated;
        template <class, class> friend class TapUninterpolated;
        template <class, class, std::size_t> friend class TapDelayUninterpolated;
        template <class, class, std::size_t> friend class TapDelayInterpolated;
    };

}

#endif /* MD_AUDIO_WRITER_HPP */
