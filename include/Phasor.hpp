#ifndef MD_AUDIO_PHASOR_HPP
#define MD_AUDIO_PHASOR_HPP

#include "constants.hpp"
#include "interfaces/Generatable.hpp"
#include "interfaces/Processable.hpp"
#include "types.hpp"
#include "utility.hpp"

namespace md_audio {

    class Phasor : public Generatable<MdFloat>, public Processable<MdFloat, MdFloat> {
    public:
        Phasor() = default;

        explicit Phasor(MdFloat);

        explicit Phasor(MdFloat, MdFloat);

        inline void set_frequency(MdFloat frequency) noexcept {
            m_rate = static_cast<double>(
                utility::clip(frequency, static_cast<MdFloat>(-half_sample_rate), static_cast<MdFloat>(half_sample_rate))
            ) * sample_duration;
        }

        inline void set_phase(MdFloat phase) noexcept {
            m_level = utility::clip(phase, static_cast<MdFloat>(0), static_cast<MdFloat>(1));
        }

        MdFloat perform(void) noexcept override final;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        double m_rate;
        double m_level = 0.;
        MdFloat m_previous = 0.;
    };

}

#endif /* MD_AUDIO_PHASOR_HPP */
