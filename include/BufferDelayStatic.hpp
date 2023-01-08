#ifndef MD_AUDIO_BUFFER_DELAY_STATIC_HPP
#define MD_AUDIO_BUFFER_DELAY_STATIC_HPP

#include "BufferDelay.hpp"
#include "Reader.hpp"
#include "TapUninterpolated.hpp"

namespace md_audio {

    template <class Allocator>
    class BufferDelayStatic : public BufferDelay<Allocator, Reader<Allocator>, TapUninterpolated<Allocator, Reader<Allocator>>> {
    public:
        explicit BufferDelayStatic(Buffer<Allocator>& buffer, double max_delay_time) :
            BufferDelay<Allocator, Reader<Allocator>, TapUninterpolated<Allocator, Reader<Allocator>>>(buffer, max_delay_time)
        {}

        explicit BufferDelayStatic(Buffer<Allocator>& buffer, double max_delay_time, double delay_time) :
            BufferDelay<Allocator, Reader<Allocator>, TapUninterpolated<Allocator, Reader<Allocator>>>(buffer, max_delay_time, delay_time)
        {}
    };

}

#endif /* MD_AUDIO_BUFFER_DELAY_STATIC_HPP */
