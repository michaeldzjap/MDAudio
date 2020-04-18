#ifndef MD_AUDIO_REVERSIBLE_DELAY_HPP
#define MD_AUDIO_REVERSIBLE_DELAY_HPP

#include "HannOscillator.hpp"
#include "Phasor.hpp"
#include "Processable.hpp"
#include "TapDelayCubic.hpp"
#include <array>
#include <cstdint>

namespace md_audio {

    template <
        typename Allocator,
        std::size_t overlap = 2,
        typename Delay = TapDelayCubic<Allocator, 3> // One extra tap for "forward" mode
    >
    class ReversibleDelay : public Processable<MdFloat, MdFloat> {
    public:
        static_assert(overlap > 1, "Overlap factor must be at least 2!");

        explicit ReversibleDelay(Allocator&, MdFloat);

        explicit ReversibleDelay(Allocator&, MdFloat, MdFloat);

        explicit ReversibleDelay(Allocator&, MdFloat, MdFloat, bool);

        void initialise();

        void set_backward_delay(MdFloat) noexcept;

        void set_forward_delay(MdFloat) noexcept;

        inline void set_reverse(bool) noexcept;

        inline void toggle_reverse() noexcept;

        inline bool is_reversed() const noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        Delay m_delay;
        std::array<Phasor, overlap> m_phasor;
        std::array<HannOscillator, overlap> m_osc;
        MdFloat m_size;
        MdFloat m_frequency;
        bool m_reverse = false;
        const MdFloat m_norm = static_cast<MdFloat>(2) / overlap;

        void initialise(MdFloat) noexcept;

        static constexpr MdFloat compute_frequency(MdFloat) noexcept;
    };

    template <typename Allocator, std::size_t overlap, typename Delay>
    ReversibleDelay<Allocator, overlap, Delay>::ReversibleDelay(Allocator& allocator,
        MdFloat max_delay) :
        m_delay(allocator, max_delay),
        m_reverse(false)
    {
        initialise(static_cast<MdFloat>(0.));
    }

    template <typename Allocator, std::size_t overlap, typename Delay>
    ReversibleDelay<Allocator, overlap, Delay>::ReversibleDelay(Allocator& allocator,
        MdFloat max_delay, MdFloat size) :
        m_delay(allocator, max_delay),
        m_reverse(false)
    {
        initialise(size);
    }

    template <typename Allocator, std::size_t overlap, typename Delay>
    ReversibleDelay<Allocator, overlap, Delay>::ReversibleDelay(Allocator& allocator,
        MdFloat max_delay, MdFloat size, bool reverse) :
        m_delay(allocator, max_delay),
        m_reverse(reverse)
    {
        initialise(size);
    }

    template <typename Allocator, std::size_t overlap, typename Delay>
    void ReversibleDelay<Allocator, overlap, Delay>::initialise() {
        m_delay.initialise();
    }

    template <typename Allocator, std::size_t overlap, typename Delay>
    void ReversibleDelay<Allocator, overlap, Delay>::initialise(MdFloat size) noexcept {
        set_forward_delay(size);
        set_backward_delay(size);

        for (auto i = 0; i < overlap; i++)
            m_phasor[i].set_phase(static_cast<MdFloat>(i) / static_cast<MdFloat>(overlap));
    }

    template <typename Allocator, std::size_t overlap, typename Delay>
    inline void ReversibleDelay<Allocator, overlap, Delay>::set_backward_delay(MdFloat size) noexcept {
        m_size = utility::clip(size, static_cast<MdFloat>(5), m_delay.get_max_delay());
        m_frequency = compute_frequency(m_size);

        for (auto& p : m_phasor)
            p.set_frequency(m_frequency);
    }

    template <typename Allocator, std::size_t overlap, typename Delay>
    void ReversibleDelay<Allocator, overlap, Delay>::set_forward_delay(MdFloat delay) noexcept {
        m_delay.set_delay(overlap, delay);
    }

    template <typename Allocator, std::size_t overlap, typename Delay>
    void ReversibleDelay<Allocator, overlap, Delay>::set_reverse(bool reverse) noexcept {
        m_reverse = reverse;
    }

    template <typename Allocator, std::size_t overlap, typename Delay>
    void ReversibleDelay<Allocator, overlap, Delay>::toggle_reverse() noexcept {
        m_reverse = !m_reverse;
    }

    template <typename Allocator, std::size_t overlap, typename Delay>
    bool ReversibleDelay<Allocator, overlap, Delay>::is_reversed() const noexcept {
        return m_reverse;
    }

    template <typename Allocator, std::size_t overlap, typename Delay>
    MdFloat ReversibleDelay<Allocator, overlap, Delay>::perform(MdFloat in) noexcept {
        auto z = static_cast<MdFloat>(0);

        m_delay.write(in); // Write the next sample to the delay buffer

        if (m_reverse) {
            for (auto i = 0; i < overlap; i++) {
                auto phase = m_phasor[i].perform();

                m_osc[i].set_phase(static_cast<MdFloat>(phase * two_pi));

                auto window = m_osc[i].perform();

                m_delay.set_delay(i, phase * m_size);

                z += m_delay.read(i) * window;
            }

            z *= m_norm;
        } else
            z = m_delay.read(overlap);

        m_delay.increment(); // Increment the write pointer

        return z;
    }

    template <typename Allocator, std::size_t overlap, typename Delay>
    inline constexpr MdFloat ReversibleDelay<Allocator, overlap, Delay>::compute_frequency(MdFloat size) noexcept {
        return static_cast<MdFloat>(2) * static_cast<MdFloat>(sample_rate) / size;
    }

}

#endif /* MD_AUDIO_REVERSIBLE_DELAY_HPP */
