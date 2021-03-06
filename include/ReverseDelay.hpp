#ifndef MD_AUDIO_REVERSE_DELAY_HPP
#define MD_AUDIO_REVERSE_DELAY_HPP

#include "HannOscillator.hpp"
#include "Phasor.hpp"
#include "TapDelayLinear.hpp"
#include "interfaces/Processable.hpp"

namespace md_audio {

    class ReverseDelay : public Processable<MdFloat, MdFloat> {
    public:
        explicit ReverseDelay(memory::Poolable&, MdFloat, std::size_t);

        explicit ReverseDelay(memory::Poolable&, MdFloat, MdFloat, std::size_t);

        void set_size(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

        static void set_sample_rate(double) noexcept;

        ~ReverseDelay();

    private:
        const MdFloat m_max_delay;
        MdFloat m_size;
        const std::size_t m_overlap;
        const MdFloat m_norm;
        memory::Poolable& m_pool;
        TapDelayLinear m_delay;
        Phasor* m_phasor = nullptr;
        HannOscillator* m_osc = nullptr;

        void initialise(MdFloat);

        inline static constexpr MdFloat compute_frequency(MdFloat) noexcept;
    };

    constexpr MdFloat ReverseDelay::compute_frequency(MdFloat size) noexcept {
        return static_cast<MdFloat>(2) / size;
    }

}

#endif /* MD_AUDIO_REVERSE_DELAY_HPP */
