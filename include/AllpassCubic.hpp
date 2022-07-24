#ifndef MD_AUDIO_ALLPASS_CUBIC_HPP
#define MD_AUDIO_ALLPASS_CUBIC_HPP

#include "Allpass.hpp"
#include "ReaderCubic.hpp"
#include "TapInterpolated.hpp"

namespace md_audio {

    template <class Allocator>
    class AllpassCubic : public Allpass<Allocator, ReaderCubic<Allocator>, TapInterpolated<Allocator, ReaderCubic<Allocator>>> {
    public:
        explicit AllpassCubic(Allocator& allocator, double max_delay_time) :
            Allpass<Allocator, ReaderCubic<Allocator>, TapInterpolated<Allocator, ReaderCubic<Allocator>>>(allocator, max_delay_time)
        {}

        explicit AllpassCubic(Allocator& allocator, double max_delay_time, double delay_time) :
            Allpass<Allocator, ReaderCubic<Allocator>, TapInterpolated<Allocator, ReaderCubic<Allocator>>>(allocator, max_delay_time, delay_time)
        {}

        explicit AllpassCubic(Allocator& allocator, double max_delay_time, double delay_time, double gain) :
            Allpass<Allocator, ReaderCubic<Allocator>, TapInterpolated<Allocator, ReaderCubic<Allocator>>>(allocator, max_delay_time, delay_time, gain)
        {}
    };

}

#endif /* MD_AUDIO_ALLPASS_CUBIC_HPP */
