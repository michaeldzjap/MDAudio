#ifndef MD_AUDIO_ALLPASS_STATIC_HPP
#define MD_AUDIO_ALLPASS_STATIC_HPP

#include "Allpass.hpp"
#include "Reader.hpp"
#include "TapUninterpolated.hpp"

namespace md_audio {

    template <class Allocator>
    class AllpassStatic : public Allpass<Allocator, Reader<Allocator>, TapUninterpolated<Allocator, Reader<Allocator>>> {
    public:
        explicit AllpassStatic(Allocator& allocator, double max_delay_time) :
            Allpass<Allocator, Reader<Allocator>, TapUninterpolated<Allocator, Reader<Allocator>>>(allocator, max_delay_time)
        {}

        explicit AllpassStatic(Allocator& allocator, double max_delay_time, double delay_time) :
            Allpass<Allocator, Reader<Allocator>, TapUninterpolated<Allocator, Reader<Allocator>>>(allocator, max_delay_time, delay_time)
        {}

        explicit AllpassStatic(Allocator& allocator, double max_delay_time, double delay_time, double gain) :
            Allpass<Allocator, Reader<Allocator>, TapUninterpolated<Allocator, Reader<Allocator>>>(allocator, max_delay_time, delay_time, gain)
        {}
    };

}

#endif /* MD_AUDIO_ALLPASS_STATIC_HPP */
