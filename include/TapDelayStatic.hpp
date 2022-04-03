#ifndef MD_AUDIO_TAP_DELAY_STATIC_HPP
#define MD_AUDIO_TAP_DELAY_STATIC_HPP

#include <array>
#include "TapDelayUninterpolated.hpp"
#include "Reader.hpp"

namespace md_audio {

    template <class Allocator, std::size_t TAPS = 2>
    class TapDelayStatic : public TapDelayUninterpolated<Allocator, Reader<Allocator>, TAPS> {
    public:
        explicit TapDelayStatic(Allocator& allocator, double max_delay_time) :
            TapDelayUninterpolated<Allocator, Reader<Allocator>, TAPS>(allocator, max_delay_time)
        {}

        explicit TapDelayStatic(Allocator& allocator, double max_delay_time, std::array<double, TAPS>& delay_times) :
            TapDelayUninterpolated<Allocator, Reader<Allocator>, TAPS>(allocator, max_delay_time, delay_times)
        {}
    };

}

#endif /* MD_AUDIO_TAP_DELAY_STATIC_HPP */
