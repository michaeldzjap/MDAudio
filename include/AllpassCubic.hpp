#ifndef MD_AUDIO_ALLPASS_CUBIC_HPP
#define MD_AUDIO_ALLPASS_CUBIC_HPP

#include "AllpassInterpolated.hpp"
#include "ReaderCubic.hpp"

namespace md_audio {

    template <typename T>
    using Base = AllpassInterpolated<T, ReaderCubic<T>>;

    template <class Allocator>
    class AllpassCubic : public Base<Allocator> {
    public:
        explicit AllpassCubic(Allocator& allocator, double max_delay_time) :
            Base<Allocator>(allocator, max_delay_time)
        {}

        explicit AllpassCubic(Allocator& allocator, double max_delay_time, double delay_time) :
            Base<Allocator>(allocator, max_delay_time, delay_time)
        {}

        explicit AllpassCubic(Allocator& allocator, double max_delay_time, double delay_time, double gain) :
            Base<Allocator>(allocator, max_delay_time, delay_time, gain)
        {}
    };

}

#endif /* MD_AUDIO_ALLPASS_CUBIC_HPP */
