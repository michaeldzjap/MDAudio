#ifndef MD_AUDIO_BUFFER_DELAY_LINEAR_HPP
#define MD_AUDIO_BUFFER_DELAY_LINEAR_HPP

#include "BufferDelay.hpp"
#include "ReaderLinear.hpp"
#include "TapInterpolated.hpp"

namespace md_audio {

    template <class Allocator>
    class BufferDelayLinear : public BufferDelay<Allocator, ReaderLinear<Allocator>, TapInterpolated<Allocator, ReaderLinear<Allocator>>> {
    public:
        explicit BufferDelayLinear(Buffer<Allocator>& buffer, double max_delay_time) :
            BufferDelay<Allocator, ReaderLinear<Allocator>, TapInterpolated<Allocator, ReaderLinear<Allocator>>>(buffer, max_delay_time)
        {}

        explicit BufferDelayLinear(Buffer<Allocator>& buffer, double max_delay_time, double delay_time) :
            BufferDelay<Allocator, ReaderLinear<Allocator>, TapInterpolated<Allocator, ReaderLinear<Allocator>>>(buffer, max_delay_time, delay_time)
        {}
    };

}

#endif /* MD_AUDIO_BUFFER_DELAY_LINEAR_HPP */
