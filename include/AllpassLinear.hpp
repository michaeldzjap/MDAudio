#ifndef MD_AUDIO_ALLPASS_LINEAR_HPP
#define MD_AUDIO_ALLPASS_LINEAR_HPP

#include "Allpass.hpp"
#include "ReaderLinear.hpp"
#include "TapInterpolated.hpp"

namespace md_audio {

    template <class Allocator>
    class AllpassLinear : public Allpass<Allocator, ReaderLinear<Allocator>, TapInterpolated<Allocator, ReaderLinear<Allocator>>> {
    public:
        explicit AllpassLinear(Allocator& allocator, double max_delay_time) :
            Allpass<Allocator, ReaderLinear<Allocator>, TapInterpolated<Allocator, ReaderLinear<Allocator>>>(allocator, max_delay_time)
        {}

        explicit AllpassLinear(Allocator& allocator, double max_delay_time, double delay_time) :
            Allpass<Allocator, ReaderLinear<Allocator>, TapInterpolated<Allocator, ReaderLinear<Allocator>>>(allocator, max_delay_time, delay_time)
        {}

        explicit AllpassLinear(Allocator& allocator, double max_delay_time, double delay_time, double gain) :
            Allpass<Allocator, ReaderLinear<Allocator>, TapInterpolated<Allocator, ReaderLinear<Allocator>>>(allocator, max_delay_time, delay_time, gain)
        {}
    };

}

#endif /* MD_AUDIO_ALLPASS_LINEAR_HPP */
