#ifndef MD_AUDIO_ZDF_HPP
#define MD_AUDIO_ZDF_HPP

#include "constants.hpp"
#include "utility.hpp"
#include <cmath>

namespace md_audio {

    inline auto g(const double frequency) noexcept {
        return std::tan(utility::clip(frequency, 0., half_sample_rate) * pi_over_sample_rate);
    }

    inline auto m2(double gain) noexcept {
        return std::pow(10., gain / 20.);
    }

    inline auto r2(double r) noexcept {
        r = utility::max(r, 0.);

        return r + r;
    }

    inline auto d(double r2, double g) noexcept {
        return 1. / (1. + r2 * g + g * g);
    }

}

#endif /* MD_AUDIO_ZDF_HPP */
