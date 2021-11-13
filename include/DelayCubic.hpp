#ifndef MD_AUDIO_DELAY_CUBIC_HPP
#define MD_AUDIO_DELAY_CUBIC_HPP

#include "DelayInterpolated.hpp"
#include "ReaderCubic.hpp"

namespace md_audio {

    template <class Allocator>
    class DelayCubic : public DelayInterpolated<Allocator, ReaderCubic<Allocator>> {
    public:
        explicit DelayCubic(Allocator& allocator, double max_delay_time) :
            DelayInterpolated<Allocator, ReaderCubic<Allocator>>(allocator, max_delay_time)
        {}

        explicit DelayCubic(Allocator& allocator, double max_delay_time, double delay_time) :
            DelayInterpolated<Allocator, ReaderCubic<Allocator>>(allocator, max_delay_time, delay_time)
        {}
    };

}

#endif /* MD_AUDIO_DELAY_CUBIC_HPP */
