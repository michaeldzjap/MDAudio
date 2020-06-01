#ifndef MD_AUDIO_REVERSE_DELAY_HPP
#define MD_AUDIO_REVERSE_DELAY_HPP

#include "HannOscillator.hpp"
#include "InterpolationType.hpp"
#include "Phasor.hpp"
#include "Processable.hpp"
#include "TapDelay.hpp"
#include "types.hpp"

namespace md_audio {

    class ReverseDelay : public Processable<MdFloat, MdFloat> {
    public:
        explicit ReverseDelay(memory::Poolable&, std::size_t, std::size_t, InterpolationType = InterpolationType::linear);

        explicit ReverseDelay(memory::Poolable&, std::size_t, MdFloat, std::size_t, InterpolationType = InterpolationType::linear);

        void initialise();

        void set_size(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

        ~ReverseDelay();

    private:
        memory::Poolable& m_pool;
        TapDelay m_delay;
        Phasor* m_phasor = nullptr;
        HannOscillator* m_osc = nullptr;
        MdFloat m_size;
        std::size_t m_overlap;
        const MdFloat m_norm;

        void initialise(MdFloat);

        void* allocate(std::size_t size);

        inline static constexpr MdFloat compute_frequency(MdFloat) noexcept;
    };

    constexpr MdFloat ReverseDelay::compute_frequency(MdFloat size) noexcept {
        return static_cast<MdFloat>(2) * static_cast<MdFloat>(sample_rate) / size;
    }

}

#endif /* MD_AUDIO_REVERSE_DELAY_HPP */
