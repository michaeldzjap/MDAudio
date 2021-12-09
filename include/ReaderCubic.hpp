#ifndef MD_AUDIO_READER_CUBIC_HPP
#define MD_AUDIO_READER_CUBIC_HPP

#include <cstddef>
#include "Buffer.hpp"
#include "utility.hpp"

using md_audio::Buffer;
using md_audio::utility::interpolate_cubic;

namespace md_audio {

    template <class Allocator>
    class ReaderCubic {
    public:
        explicit ReaderCubic(Buffer<Allocator>& buffer) :
            m_buffer(buffer),
            m_mask(m_buffer.m_size - 1)
        {}

        double read(std::size_t read_index, double frac) const noexcept {
            auto phase_1 = read_index & m_mask;
            auto phase_2 = (phase_1 - 1) & m_mask;
            auto phase_3 = (phase_1 - 2) & m_mask;
            auto phase_0 = (phase_1 + 1) & m_mask;

            return interpolate_cubic(
                frac,
                m_buffer[phase_0],
                m_buffer[phase_1],
                m_buffer[phase_2],
                m_buffer[phase_3]
            );
        }

        private:
            Buffer<Allocator>& m_buffer;
            std::size_t m_mask;
    };

}

#endif /* MD_AUDIO_READER_CUBIC_HPP */
