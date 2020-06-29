#ifndef MD_AUDIO_PHASOR_HPP
#define MD_AUDIO_PHASOR_HPP

#include "SampleRate.hpp"
#include "interfaces/Generatable.hpp"
#include "interfaces/Processable.hpp"
#include "types.hpp"
#include "utility.hpp"

namespace md_audio {

    class Phasor :
        public SampleRate,
        public Generatable<MdFloat>,
        public Processable<MdFloat, MdFloat>
    {
    public:
        explicit Phasor();

        explicit Phasor(MdFloat);

        explicit Phasor(MdFloat, MdFloat);

        inline void set_frequency(MdFloat) noexcept;

        inline void set_phase(MdFloat) noexcept;

        MdFloat perform(void) noexcept override final;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        double m_rate;
        double m_level = 0.;
        MdFloat m_previous = 0.;
    };

    void Phasor::set_frequency(MdFloat frequency) noexcept {
        m_rate = static_cast<double>(
            utility::clip(
                frequency,
                static_cast<MdFloat>(-m_half_sample_rate),
                static_cast<MdFloat>(m_half_sample_rate)
            )
        ) * m_sample_duration;
    }

    void Phasor::set_phase(MdFloat phase) noexcept {
        m_level = utility::clip(phase, static_cast<MdFloat>(0), static_cast<MdFloat>(1));
    }

}

#endif /* MD_AUDIO_PHASOR_HPP */
