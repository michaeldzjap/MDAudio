#ifndef MD_AUDIO_ZDF_HPP
#define MD_AUDIO_ZDF_HPP

#include "constants.hpp"
#include "types.hpp"
#include "utility.hpp"
#include <cmath>

namespace md_audio {

    class Zdf {
    public:
        inline virtual void set_frequency(MdFloat frequency) noexcept {
            m_g = compute_g(static_cast<double>(frequency));
        }

        virtual ~Zdf() = 0;

    protected:
        double m_g;

    private:
        static constexpr double pi_over_sample_rate = pi * sample_duration;

        inline static double compute_g(double frequency) noexcept {
            return std::tan(
                utility::clip(frequency, 0., half_sample_rate) * pi_over_sample_rate
            );
        }
    };

}

#endif /* MD_AUDIO_ZDF_HPP */
