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
        explicit VariableDelay(memory::Poolable&, MdFloat, std::size_t);

        explicit VariableDelay(memory::Poolable&, MdFloat, MdFloat, std::size_t);

        explicit VariableDelay(memory::Poolable&, MdFloat, MdFloat, MdFloat, std::size_t);

        inline void set_delay(MdFloat) noexcept;

        void set_size(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

        static void set_sample_rate(double) noexcept;

        ~VariableDelay();

    private:
        const MdFloat m_max_delay;
        MdFloat m_delay_time;
        const std::size_t m_overlap;
        const MdFloat m_norm;
        memory::Poolable& m_pool;
        TapDelayStatic m_delay;
        Phasor* m_phasor = nullptr;
        HannOscillator* m_osc = nullptr;
        Latch* m_latch = nullptr;

        void initialise(MdFloat, MdFloat);

        inline static constexpr MdFloat compute_frequency(MdFloat) noexcept;
    };

    void VariableDelay::set_delay(MdFloat delay) noexcept {
        m_delay_time = utility::clip<MdFloat>(delay, .01, m_max_delay);
    }

    constexpr MdFloat VariableDelay::compute_frequency(MdFloat size) noexcept {
        return static_cast<MdFloat>(1) / size;
    }

}

#endif /* MD_AUDIO_VARIABLE_DELAY */
