#ifndef MD_AUDIO_OSCILLATOR_HPP
#define MD_AUDIO_OSCILLATOR_HPP

#include "constants.hpp"
#include "tables.hpp"
#include "types.hpp"
#include "utility.hpp"
#include <array>

namespace md_audio {

    class Oscillator {
    public:
        Oscillator() = default;

        explicit Oscillator(MdFloat);

        explicit Oscillator(MdFloat, MdFloat);

        inline void set_frequency(MdFloat frequency) noexcept {
            m_frequency_rate = cycles_to_increment * static_cast<double>(
                utility::clip(frequency, static_cast<MdFloat>(-half_sample_rate), static_cast<MdFloat>(half_sample_rate))
            );
        }

        inline void set_phase(MdFloat phase) noexcept {
            m_phase_rate = radians_to_increment * static_cast<double>(phase);
        }

        virtual ~Oscillator() = 0;

    protected:
        MdFloat perform(const std::array<MdFloat, table_size + 1>&) noexcept;

    private:
        double m_phase_acc = 0.;
        double m_phase_rate = 0.;
        double m_frequency_rate = 0.;
    };

}

#endif /* MD_AUDIO_OSCILLATOR_HPP */
