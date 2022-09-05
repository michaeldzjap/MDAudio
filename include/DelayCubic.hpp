#ifndef MD_AUDIO_DELAY_CUBIC_HPP
#define MD_AUDIO_DELAY_CUBIC_HPP

#include "Delay.hpp"
#include "ReaderCubic.hpp"
#include "TapInterpolated.hpp"

namespace md_audio {

    template <class Allocator>
    class DelayCubic : public Delay<Allocator, ReaderCubic<Allocator>, TapInterpolated<Allocator, ReaderCubic<Allocator>>> {
    public:
        explicit DelayCubic(Allocator& allocator, double max_delay_time) :
            Delay<Allocator, ReaderCubic<Allocator>, TapInterpolated<Allocator, ReaderCubic<Allocator>>>(allocator, max_delay_time)
        {}

        explicit DelayCubic(Allocator& allocator, double max_delay_time, double delay_time) :
            Delay<Allocator, ReaderCubic<Allocator>, TapInterpolated<Allocator, ReaderCubic<Allocator>>>(allocator, max_delay_time, delay_time)
        {}
    };

}

#endif /* MD_AUDIO_DELAY_CUBIC_HPP */
