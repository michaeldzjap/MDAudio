#ifndef MD_AUDIO_ALLPASS_LINEAR_HPP
#define MD_AUDIO_ALLPASS_LINEAR_HPP

#include "AllpassInterpolated.hpp"
#include "ReaderLinear.hpp"

namespace md_audio {

    template <class Allocator>
    class AllpassLinear : public AllpassInterpolated<Allocator, ReaderLinear<Allocator>> {
    public:
        explicit AllpassLinear(Allocator& allocator, double max_delay_time) :
            AllpassInterpolated<Allocator, ReaderLinear<Allocator>>(allocator, max_delay_time)
        {}

        explicit AllpassLinear(Allocator& allocator, double max_delay_time, double delay_time) :
            AllpassInterpolated<Allocator, ReaderLinear<Allocator>>(allocator, max_delay_time, delay_time)
        {}

        explicit AllpassLinear(Allocator& allocator, double max_delay_time, double delay_time, double gain) :
            AllpassInterpolated<Allocator, ReaderLinear<Allocator>>(allocator, max_delay_time, delay_time, gain)
        {}
    };

}

#endif /* MD_AUDIO_ALLPASS_LINEAR_HPP */
