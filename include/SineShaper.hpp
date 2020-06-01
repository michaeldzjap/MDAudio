#ifndef MD_AUDIO_SINE_SHAPER_HPP
#define MD_AUDIO_SINE_SHAPER_HPP

#include "constants.hpp"
#include "interfaces/Processable.hpp"
#include "tables.hpp"
#include "types.hpp"
#include "utility.hpp"

namespace md_audio {

    class SineShaper : public Processable<MdFloat, MdFloat> {
    public:
        SineShaper() = default;

        explicit SineShaper(MdFloat);

        inline void set_limit(MdFloat limit) noexcept {
            if (limit != 0.) {
                m_limit = limit;
                m_phase_rate = 1. / static_cast<double>(m_limit) * radians_to_increment;
            }
        }

        MdFloat perform(MdFloat) noexcept override final;

    private:
        MdFloat m_limit = static_cast<MdFloat>(1);
        double m_phase_rate = radians_to_increment;
    };

}

#endif /* MD_AUDIO_SINE_SHAPER_HPP */
