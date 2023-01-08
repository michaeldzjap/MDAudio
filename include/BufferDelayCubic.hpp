#ifndef MD_AUDIO_BUFFER_DELAY_CUBIC_HPP
#define MD_AUDIO_BUFFER_DELAY_CUBIC_HPP

#include "BufferDelay.hpp"
#include "ReaderCubic.hpp"
#include "TapInterpolated.hpp"

namespace md_audio {

    template <class Allocator>
    class BufferDelayCubic : public BufferDelay<Allocator, ReaderCubic<Allocator>, TapInterpolated<Allocator, ReaderCubic<Allocator>>> {
    public:
        explicit BufferDelayCubic(Buffer<Allocator>& buffer, double max_delay_time) :
            BufferDelay<Allocator, ReaderCubic<Allocator>, TapInterpolated<Allocator, ReaderCubic<Allocator>>>(buffer, max_delay_time)
        {}

        explicit BufferDelayCubic(Buffer<Allocator>& buffer, double max_delay_time, double delay_time) :
            BufferDelay<Allocator, ReaderCubic<Allocator>, TapInterpolated<Allocator, ReaderCubic<Allocator>>>(buffer, max_delay_time, delay_time)
        {}
    };

}

#endif /* MD_AUDIO_BUFFER_DELAY_CUBIC_HPP */
