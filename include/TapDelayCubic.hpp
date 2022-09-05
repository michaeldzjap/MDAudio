#ifndef MD_AUDIO_TAP_DELAY_CUBIC_HPP
#define MD_AUDIO_TAP_DELAY_CUBIC_HPP

#include <array>
#include "TapDelay.hpp"
#include "TapInterpolated.hpp"
#include "ReaderCubic.hpp"

namespace md_audio {

    template <class Allocator, std::size_t TAPS = 2>
    class TapDelayCubic : public TapDelay<Allocator, ReaderCubic<Allocator>, TapInterpolated<Allocator, ReaderCubic<Allocator>>, TAPS> {
    public:
        explicit TapDelayCubic(Allocator& allocator, double max_delay_time) :
            TapDelay<Allocator, ReaderCubic<Allocator>, TapInterpolated<Allocator, ReaderCubic<Allocator>>, TAPS>(allocator, max_delay_time)
        {}

        explicit TapDelayCubic(Allocator& allocator, double max_delay_time, std::array<double, TAPS>& delay_times) :
            TapDelay<Allocator, ReaderCubic<Allocator>, TapInterpolated<Allocator, ReaderCubic<Allocator>>, TAPS>(allocator, max_delay_time, delay_times)
        {}
    };

}

#endif /* MD_AUDIO_TAP_DELAY_CUBIC_HPP */
