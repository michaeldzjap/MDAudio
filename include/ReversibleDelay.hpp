#ifndef MD_AUDIO_REVERSIBLE_DELAY_HPP
#define MD_AUDIO_REVERSIBLE_DELAY_HPP

#include "HannOscillator.hpp"
#include "Phasor.hpp"
#include "TapDelayLinear.hpp"
#include "interfaces/Processable.hpp"
#include "types.hpp"

namespace md_audio {

    class ReversibleDelay : public Processable<MdFloat, MdFloat> {
    public:
        explicit ReversibleDelay(memory::Poolable&, MdFloat, std::size_t);

        explicit ReversibleDelay(memory::Poolable&, MdFloat, MdFloat, std::size_t);

        explicit ReversibleDelay(memory::Poolable&, MdFloat, bool, std::size_t);

        explicit ReversibleDelay(memory::Poolable&, MdFloat, MdFloat, bool, std::size_t);

        void set_backward_delay(MdFloat) noexcept;

        void set_forward_delay(MdFloat) noexcept;

        inline void set_reverse(bool) noexcept;

        inline void toggle_reverse() noexcept;

        inline bool is_reversed() const noexcept;

        MdFloat perform(MdFloat) noexcept override final;

        ~ReversibleDelay();

    private:
        const MdFloat m_max_delay;
        MdFloat m_size;
        const std::size_t m_overlap;
        bool m_reverse;
        const MdFloat m_norm;
        memory::Poolable& m_pool;
        TapDelayLinear m_delay;
        Phasor* m_phasor = nullptr;
        HannOscillator* m_osc = nullptr;

        void initialise(MdFloat);

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
        return static_cast<MdFloat>(2) / size;
    }

}

#endif /* MD_AUDIO_REVERSIBLE_DELAY_HPP */
