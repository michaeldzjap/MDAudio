#ifndef MD_AUDIO_REVERSE_DELAY_HPP
#define MD_AUDIO_REVERSE_DELAY_HPP

#include "HannOscillator.hpp"
#include "Phasor.hpp"
#include "Processable.hpp"
#include "TapDelayCubic.hpp"
#include <array>
#include <cstdint>

namespace md_audio {

    template <std::uint16_t OVERLAP = 2, typename Delay = TapDelayCubic<OVERLAP>>
    class ReverseDelay : public Processable<MdFloat, MdFloat> {
    public:
        static_assert(OVERLAP > 1, "Overlap factor must be at least 2!");

        explicit ReverseDelay(memory::Allocatable<MdFloat*>&, MdFloat);

        explicit ReverseDelay(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat);

        void initialise();

        void set_size(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        Delay m_delay;
        std::array<Phasor, OVERLAP> m_phasor;
        std::array<HannOscillator, OVERLAP> m_osc;
        MdFloat m_size;
        const MdFloat m_norm = static_cast<MdFloat>(2) / OVERLAP;

        void initialise(MdFloat) noexcept;

        inline static constexpr MdFloat compute_frequency(MdFloat) noexcept;
    };

    template <std::uint16_t OVERLAP, typename Delay>
    ReverseDelay<OVERLAP, Delay>::ReverseDelay(memory::Allocatable<MdFloat*>& allocator,
        MdFloat max_delay) :
        m_delay(allocator, max_delay)
    {
        initialise(static_cast<MdFloat>(1));
    }

    template <std::uint16_t OVERLAP, typename Delay>
    ReverseDelay<OVERLAP, Delay>::ReverseDelay(memory::Allocatable<MdFloat*>& allocator,
        MdFloat max_delay, MdFloat size) :
        m_delay(allocator, max_delay)
    {
        initialise(size);
    }

    template <std::uint16_t OVERLAP, typename Delay>
    void ReverseDelay<OVERLAP, Delay>::initialise() {
        m_delay.initialise();
    }

    template <std::uint16_t OVERLAP, typename Delay>
    void ReverseDelay<OVERLAP, Delay>::initialise(MdFloat size) noexcept {
        set_size(size);

        for (auto i = 0; i < OVERLAP; i++)
            m_phasor[i].set_phase(static_cast<MdFloat>(i) / static_cast<MdFloat>(OVERLAP));
    }

    template <std::uint16_t OVERLAP, typename Delay>
    void ReverseDelay<OVERLAP, Delay>::set_size(MdFloat size) noexcept {
        m_size = utility::clip(size, static_cast<MdFloat>(5), m_delay.get_max_delay());

        auto frequency = compute_frequency(m_size);

        for (auto& p : m_phasor)
            p.set_frequency(frequency);
    }

    template <std::uint16_t OVERLAP, typename Delay>
    MdFloat ReverseDelay<OVERLAP, Delay>::perform(MdFloat in) noexcept {
        auto z = static_cast<MdFloat>(0);

        for (auto i = 0; i < OVERLAP; i++) {
            auto phase = m_phasor[i].perform();

            m_osc[i].set_phase(static_cast<MdFloat>(phase * two_pi));

            auto window = m_osc[i].perform();

            m_delay.set_delay(i, phase * m_size);

            z += m_delay.read(i) * window;
        }

        m_delay.write(in); // Write the next sample to the delay buffer

        return z * m_norm;
    }

    template <std::uint16_t OVERLAP, typename Delay>
    constexpr MdFloat ReverseDelay<OVERLAP, Delay>::compute_frequency(MdFloat size) noexcept {
        return static_cast<MdFloat>(2) * static_cast<MdFloat>(sample_rate) / size;
    }

}

#endif /* MD_AUDIO_REVERSE_DELAY_HPP */
