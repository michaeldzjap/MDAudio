#ifndef MD_AUDIO_REVERSIBLE_DELAY_HPP
#define MD_AUDIO_REVERSIBLE_DELAY_HPP

#include "HannOscillator.hpp"
#include "InterpolationType.hpp"
#include "Phasor.hpp"
#include "Processable.hpp"
#include "TapDelay.hpp"
#include "types.hpp"

namespace md_audio {

    class ReversibleDelay : public Processable<MdFloat, MdFloat> {
    public:
        explicit ReversibleDelay(memory::Poolable&, std::size_t, std::size_t, InterpolationType = InterpolationType::linear);

        explicit ReversibleDelay(memory::Poolable&, std::size_t, MdFloat, std::size_t, InterpolationType = InterpolationType::linear);

        explicit ReversibleDelay(memory::Poolable&, std::size_t, MdFloat, bool, std::size_t, InterpolationType = InterpolationType::linear);

        void set_backward_delay(MdFloat) noexcept;

        void set_forward_delay(MdFloat) noexcept;

        inline void set_reverse(bool) noexcept;

        inline void toggle_reverse() noexcept;

        inline bool is_reversed() const noexcept;

        MdFloat perform(MdFloat) noexcept override final;

        ~ReversibleDelay();

    private:
        memory::Poolable& m_pool;
        TapDelay m_delay;
        Phasor* m_phasor = nullptr;
        HannOscillator* m_osc = nullptr;
        MdFloat m_size;
        MdFloat m_frequency;
        bool m_reverse;
        std::size_t m_overlap;
        const MdFloat m_norm;

        void initialise(MdFloat);

        void* allocate(std::size_t size);

        inline static constexpr MdFloat compute_frequency(MdFloat) noexcept;
    };

    void ReversibleDelay::set_reverse(bool reverse) noexcept {
        m_reverse = reverse;
    }

    void ReversibleDelay::toggle_reverse() noexcept {
        m_reverse = !m_reverse;
    }

    bool ReversibleDelay::is_reversed() const noexcept {
        return m_reverse;
    }

    constexpr MdFloat ReversibleDelay::compute_frequency(MdFloat size) noexcept {
        return static_cast<MdFloat>(2) * static_cast<MdFloat>(sample_rate) / size;
    }

}

#endif /* MD_AUDIO_REVERSIBLE_DELAY_HPP */
