#ifndef MD_AUDIO_ALLPASS_LINEAR_HPP
#define MD_AUDIO_ALLPASS_LINEAR_HPP

#include "AllpassInterpolated.hpp"
#include "ReaderLinear.hpp"

namespace md_audio {

    template <typename T>
    using Base = AllpassInterpolated<T, ReaderLinear<T>>;

    template <class Allocator>
    class AllpassLinear : public Base<Allocator> {
    public:
        explicit AllpassLinear(Allocator& allocator, double max_delay_time) :
            Base<Allocator>(allocator, max_delay_time)
        {}

        explicit AllpassLinear(Allocator& allocator, double max_delay_time, double delay_time) :
            Base<Allocator>(allocator, max_delay_time, delay_time)
        {}

        explicit AllpassLinear(Allocator& allocator, double max_delay_time, double delay_time, double gain) :
            Base<Allocator>(allocator, max_delay_time, delay_time, gain)
        {}
    };

}

#endif /* MD_AUDIO_ALLPASS_LINEAR_HPP */
