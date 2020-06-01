#ifndef MD_AUDIO_VARIABLE_DELAY
#define MD_AUDIO_VARIABLE_DELAY

#include "HannOscillator.hpp"
#include "Latch.hpp"
#include "Phasor.hpp"
#include "TapDelayStatic.hpp"
#include "interfaces/Processable.hpp"

namespace md_audio {

    class VariableDelay : public Processable<MdFloat, MdFloat> {
    public:
        explicit VariableDelay(memory::Poolable&, std::size_t, std::size_t);

        explicit VariableDelay(memory::Poolable&, std::size_t, MdFloat, std::size_t);

        explicit VariableDelay(memory::Poolable&, std::size_t, MdFloat, MdFloat, std::size_t);

        inline void set_delay(MdFloat) noexcept;

        void set_size(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

        ~VariableDelay();

    private:
        memory::Poolable& m_pool;
        TapDelayStatic m_delay;
        Phasor* m_phasor = nullptr;
        HannOscillator* m_osc = nullptr;
        Latch* m_latch;
        MdFloat m_delay_samples;
        std::size_t m_overlap;
        const MdFloat m_norm;

        void initialise(MdFloat, MdFloat);

        void* allocate(std::size_t);

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
