#ifndef MD_AUDIO_READER_LINEAR_HPP
#define MD_AUDIO_READER_LINEAR_HPP

#include <cstddef>
#include "Buffer.hpp"
#include "utility.hpp"

using md_audio::Buffer;
using md_audio::utility::interpolate_linear;

namespace md_audio {

    template <class Allocator>
    class ReaderLinear {
    public:
        explicit ReaderLinear(Buffer<Allocator>& buffer) :
            m_buffer(buffer),
            m_mask(m_buffer.m_size - 1)
        {}

        double read(std::size_t read_index, double frac) const noexcept {
            auto phase_a = read_index & m_mask;
            auto phase_b = (phase_a - 1) & m_mask;

            return interpolate_linear(frac, m_buffer[phase_a], m_buffer[phase_b]);
        }

    private:
        Buffer<Allocator>& m_buffer;
        std::size_t m_mask;
    };

}

#endif /* MD_AUDIO_READER_LINEAR_HPP */
