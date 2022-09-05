#ifndef MD_AUDIO_TPT_HPP
#define MD_AUDIO_TPT_HPP

#include <cmath>
#include "constants.hpp"
#include "utility.hpp"

namespace md_audio::tpt {

    inline double g(double frequency, double half_sample_rate, double sample_duration) noexcept {
        return std::tan(
            utility::clip(frequency, 0., half_sample_rate) * PI * sample_duration
        );
    }

    inline double r2(double r) noexcept {
        r = utility::max(r, 0.);

        return r + r;
    }

    inline double d(double r2, double g) noexcept {
        return 1. / (1. + r2 * g + g * g);
    }

    inline double m2(double gain) noexcept {
        return std::pow(10., gain / 20.);
    }

}

#endif /* MD_AUDIO_TPT_HPP */
