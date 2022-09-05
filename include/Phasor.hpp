#ifndef MD_AUDIO_PHASOR_HPP
#define MD_AUDIO_PHASOR_HPP

#include "Unit.hpp"

namespace md_audio {

    class Phasor : public Unit {
    public:
        explicit Phasor();

        explicit Phasor(double frequency);

        explicit Phasor(double frequency, double phase);

        void set_frequency(double frequency) noexcept;

        void set_phase(double phase) noexcept;

        double process() noexcept;

        double process(double in) noexcept;

    private:
        double m_rate;
        double m_level = 0.;
        double m_previous = 0.;
    };

}

#endif /* MD_AUDIO_PHASOR_HPP */
