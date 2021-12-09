#ifndef MD_AUDIO_OSCILLATOR_HPP
#define MD_AUDIO_OSCILLATOR_HPP

#include <array>
#include "Unit.hpp"
#include "tables.hpp"

using md_audio::TABLE_SIZE;

namespace md_audio {

    class Oscillator : public Unit {
    public:
        Oscillator(double frequency);

        Oscillator(double frequency, double phase);

        void set_frequency(double frequency) noexcept;

        void set_phase(double phase) noexcept;

        double process(const std::array<double, TABLE_SIZE + 1>& table) noexcept;

    private:
        double m_phase_acc;
        double m_phase_rate;
        double m_frequency_rate;
        double m_cycles_to_increment;
    };

}

#endif /* MD_AUDIO_OSCILLATOR_HPP */
