#ifndef MD_AUDIO_DELAY_STATIC_HPP
#define MD_AUDIO_DELAY_STATIC_HPP

#include "Delay.hpp"
#include "Reader.hpp"
#include "TapUninterpolated.hpp"

namespace md_audio {

    template <class Allocator>
    class DelayStatic : public Delay<Allocator, Reader<Allocator>, TapUninterpolated<Allocator, Reader<Allocator>>> {
    public:
        explicit DelayStatic(Allocator& allocator, double max_delay_time) :
            Delay<Allocator, Reader<Allocator>, TapUninterpolated<Allocator, Reader<Allocator>>>(allocator, max_delay_time)
        {}

        explicit DelayStatic(Allocator& allocator, double max_delay_time, double delay_time) :
            Delay<Allocator, Reader<Allocator>, TapUninterpolated<Allocator, Reader<Allocator>>>(allocator, max_delay_time, delay_time)
        {}
    };

}

#endif /* MD_AUDIO_DELAY_STATIC_HPP */
