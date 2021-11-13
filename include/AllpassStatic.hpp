#ifndef MD_AUDIO_ALLPASS_STATIC_HPP
#define MD_AUDIO_ALLPASS_STATIC_HPP

#include "AllpassUninterpolated.hpp"
#include "Reader.hpp"

namespace md_audio {

    template <typename T>
    using Base = AllpassUninterpolated<T, Reader<T>>;

    template <class Allocator>
    class AllpassStatic : public Base<Allocator> {
    public:
        explicit AllpassStatic(Allocator& allocator, double max_delay_time) :
            Base<Allocator>(allocator, max_delay_time)
        {}

        explicit AllpassStatic(Allocator& allocator, double max_delay_time, double delay_time) :
            Base<Allocator>(allocator, max_delay_time, delay_time)
        {}

        explicit AllpassStatic(Allocator& allocator, double max_delay_time, double delay_time, double gain) :
            Base<Allocator>(allocator, max_delay_time, delay_time, gain)
        {}
    };

}

#endif /* MD_AUDIO_ALLPASS_STATIC_HPP */
