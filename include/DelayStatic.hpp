#ifndef MD_AUDIO_DELAY_STATIC_HPP
#define MD_AUDIO_DELAY_STATIC_HPP

#include "DelayUninterpolated.hpp"
#include "Reader.hpp"

namespace md_audio {

    template <typename T>
    using Base = DelayUninterpolated<T, Reader<T>>;

    template <class Allocator>
    class DelayStatic : public Base<Allocator> {
    public:
        explicit DelayStatic(Allocator& allocator, double max_delay_time) :
            Base<Allocator>(allocator, max_delay_time)
        {}

        explicit DelayStatic(Allocator& allocator, double max_delay_time, double delay_time) :
            Base<Allocator>(allocator, max_delay_time, delay_time)
        {}
    };

}

#endif /* MD_AUDIO_DELAY_STATIC_HPP */
