#ifndef MD_AUDIO_TAP_DELAY_LINEAR_HPP
#define MD_AUDIO_TAP_DELAY_LINEAR_HPP

#include <array>
#include "TapDelayInterpolated.hpp"
#include "ReaderLinear.hpp"

namespace md_audio {

    template <class Allocator, std::size_t TAPS = 2>
    class TapDelayLinear : public TapDelayInterpolated<Allocator, ReaderLinear<Allocator>, TAPS> {
    public:
        explicit TapDelayLinear(Allocator& allocator, double max_delay_time) :
            TapDelayInterpolated<Allocator, ReaderLinear<Allocator>, TAPS>(allocator, max_delay_time)
        {}

        explicit TapDelayLinear(Allocator& allocator, double max_delay_time, std::array<double, TAPS>& delay_times) :
            TapDelayInterpolated<Allocator, ReaderLinear<Allocator>, TAPS>(allocator, max_delay_time, delay_times)
        {}
    };

}

#endif /* MD_AUDIO_TAP_DELAY_LINEAR_HPP */
