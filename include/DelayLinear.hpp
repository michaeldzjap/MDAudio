#ifndef MD_AUDIO_DELAY_LINEAR_HPP
#define MD_AUDIO_DELAY_LINEAR_HPP

#include "DelayInterpolated.hpp"
#include "ReaderLinear.hpp"

namespace md_audio {

    template <class Allocator>
    class DelayLinear : public DelayInterpolated<Allocator, ReaderLinear<Allocator>> {
    public:
        explicit DelayLinear(Allocator &allocator, double max_delay_time) :
            DelayInterpolated<Allocator, ReaderLinear<Allocator>>(allocator, max_delay_time)
        {}

        explicit DelayLinear(Allocator &allocator, double max_delay_time, double delay_time) :
            DelayInterpolated<Allocator, ReaderLinear<Allocator>>(allocator, max_delay_time, delay_time)
        {}
    };

}

#endif /* MD_AUDIO_DELAY_LINEAR_HPP */
