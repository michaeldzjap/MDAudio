#ifndef MD_AUDIO_VARIABLE_DELAY
#define MD_AUDIO_VARIABLE_DELAY

#include "HannOscillator.hpp"
#include "Latch.hpp"
#include "Phasor.hpp"
#include "Processable.hpp"
#include "TapDelayStatic.hpp"

namespace md_audio {

    class VariableDelay : public Processable<MdFloat, MdFloat> {
    public:
        explicit VariableDelay(memory::Allocatable<MdFloat*>&, MdFloat, std::size_t);

        explicit VariableDelay(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat, std::size_t);

        explicit VariableDelay(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat, MdFloat, std::size_t);

        void initialise();

        inline void set_delay(MdFloat) noexcept;

        void set_size(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

        ~VariableDelay();

    private:
        TapDelayStatic m_delay;
        Phasor* m_phasor;
        HannOscillator* m_osc;
        Latch* m_latch;
        MdFloat m_delay_samples;
        std::size_t m_overlap;
        const MdFloat m_norm;

        void initialise(MdFloat, MdFloat) noexcept;

        inline static constexpr MdFloat compute_frequency(MdFloat) noexcept;
    };

    void VariableDelay::set_delay(MdFloat delay) noexcept {
        m_delay_samples = utility::clip(delay, static_cast<MdFloat>(5), m_delay.get_max_delay());;
    }

    constexpr MdFloat VariableDelay::compute_frequency(MdFloat size) noexcept {
        return static_cast<MdFloat>(sample_rate) / size;
    }

}

#endif /* MD_AUDIO_VARIABLE_DELAY */
