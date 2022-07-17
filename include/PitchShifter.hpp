#ifndef MD_AUDIO_PITCH_SHIFTER_HPP
#define MD_AUDIO_PITCH_SHIFTER_HPP

#include <array>
#include <cstddef>
#include "HannOscillator.hpp"
#include "Phasor.hpp"
#include "TapDelayLinear.hpp"
#include "Unit.hpp"
#include "constants.hpp"

namespace md_audio {

    template <class Allocator, std::size_t OVERLAP = 2, class TapDelay = TapDelayLinear<Allocator, OVERLAP>>
    class PitchShifter : public Unit {
    public:
        explicit PitchShifter(Allocator& allocator, double max_delay_time) :
            m_norm(2. / OVERLAP)
        {}

        bool initialise() noexcept {
            auto result = m_delay.initialise();

            if (!result) return result;

            for (std::size_t i = 0; i < OVERLAP; ++i) {
                m_phasor[i].set_phase(1. - static_cast<double>(i) / OVERLAP);
                m_osc[i].set_frequency(0.);
            }

            return result;
        }

        void set_transposition(double transposition) noexcept {
            //
        }

        double process(double in) noexcept {
            auto z = 0.;

             for (std::size_t i = 0; i < OVERLAP; ++i) {
                auto phase = m_phasor[i].process();

                 m_osc[i].set_phase(phase * TWO_PI);
             }
        }

    private:
        TapDelay<Allocator, OVERLAP> m_delay;
        std::array<Phasor, OVERLAP> m_phasor;
        std::array<HannOscillator, OVERLAP> m_osc;

        const double m_norm;
    };

}

#endif /* MD_AUDIO_PITCH_SHIFTER_HPP */
