#ifndef MD_AUDIO_SINE_SHAPER_HPP
#define MD_AUDIO_SINE_SHAPER_HPP

#include "Unit.hpp"
#include "tables.hpp"

namespace md_audio {

    class SineShaper : public Unit {
    public:
        explicit SineShaper(double limit);

        void set_limit(double limit) noexcept;

        double process(double in) noexcept;

    private:
        double m_limit = 1.;
        double m_phase_rate = RADIANS_TO_INCREMENT;
    };

}

#endif /* MD_AUDIO_SINE_SHAPER_HPP */
