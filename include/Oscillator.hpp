#ifndef MD_AUDIO_OSCILLATOR_HPP
#define MD_AUDIO_OSCILLATOR_HPP

#include "SampleRate.hpp"
#include "tables.hpp"
#include "types.hpp"
#include "utility.hpp"
#include <array>

namespace md_audio {

    class Oscillator : public SampleRate {
    public:
        explicit Oscillator(MdFloat);

        explicit Oscillator(MdFloat, MdFloat);

        inline void set_frequency(MdFloat) noexcept;

        inline void set_phase(MdFloat) noexcept;

        virtual ~Oscillator() = 0;

    protected:
        MdFloat perform(const std::array<MdFloat, table_size + 1>&) noexcept;

    private:
        double m_phase_acc = 0.;
        double m_phase_rate = 0.;
        double m_frequency_rate = 0.;
    };

    void Oscillator::set_frequency(MdFloat frequency) noexcept {
        m_frequency_rate = m_cycles_to_increment * utility::clip(
            static_cast<double>(frequency), -m_half_sample_rate, m_half_sample_rate
        );
    }

    void Oscillator::set_phase(MdFloat phase) noexcept {
        m_phase_rate = radians_to_increment * static_cast<double>(phase);
    }

}

#endif /* MD_AUDIO_OSCILLATOR_HPP */
