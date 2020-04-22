#ifndef MD_AUDIO_REVERSE_DELAY_HPP
#define MD_AUDIO_REVERSE_DELAY_HPP

#include "HannOscillator.hpp"
#include "Phasor.hpp"
#include "Processable.hpp"
#include "TapDelayCubic.hpp"
#include <array>
#include <cstdint>

namespace md_audio {

    template <std::size_t overlap = 2, typename Delay = TapDelayCubic<overlap>>
    class ReverseDelay : public Processable<MdFloat, MdFloat> {
    public:
        static_assert(overlap > 1, "Overlap factor must be at least 2!");

        ReverseDelay(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat);

        void initialise();

        void set_size(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        Delay m_delay;
        std::array<Phasor, overlap> m_phasor;
        std::array<HannOscillator, overlap> m_osc;
        MdFloat m_size;
        const MdFloat m_norm = static_cast<MdFloat>(2) / overlap;

        static constexpr MdFloat compute_frequency(MdFloat) noexcept;
    };

    template <std::size_t overlap, typename Delay>
    ReverseDelay<overlap, Delay>::ReverseDelay(memory::Allocatable<MdFloat*>& allocator,
        MdFloat max_delay, MdFloat size) :
        m_delay(allocator, max_delay)
    {
        set_size(size);

        for (auto i = 0; i < overlap; i++)
            m_phasor[i].set_phase(static_cast<MdFloat>(i) / static_cast<MdFloat>(overlap));
    }

    template <std::size_t overlap, typename Delay>
    void ReverseDelay<overlap, Delay>::initialise() {
        m_delay.initialise();
    }

    template <std::size_t overlap, typename Delay>
    inline void ReverseDelay<overlap, Delay>::set_size(MdFloat size) noexcept {
        m_size = utility::clip(size, static_cast<MdFloat>(5), m_delay.get_max_delay());
        auto frequency = compute_frequency(m_size);

        for (auto& p : m_phasor)
            p.set_frequency(frequency);
    }

    template <std::size_t overlap, typename Delay>
    MdFloat ReverseDelay<overlap, Delay>::perform(MdFloat in) noexcept {
        auto z = static_cast<MdFloat>(0);

        m_delay.write(in); // Write the next sample to the delay buffer

        for (auto i = 0; i < overlap; i++) {
            auto phase = m_phasor[i].perform();

            m_osc[i].set_phase(static_cast<MdFloat>(phase * two_pi));

            auto window = m_osc[i].perform();

            m_delay.set_delay(i, phase * m_size);

            z += m_delay.read(i) * window;
        }

        m_delay.increment(); // Increment the write pointer

        return z * m_norm;
    }

    template <std::size_t overlap, typename Delay>
    inline constexpr MdFloat ReverseDelay<overlap, Delay>::compute_frequency(MdFloat size) noexcept {
        return static_cast<MdFloat>(2) * static_cast<MdFloat>(sample_rate) / size;
    }

}

#endif /* MD_AUDIO_REVERSE_DELAY_HPP */
