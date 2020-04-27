#ifndef MD_AUDIO_PITCH_SHIFTER_HPP
#define MD_AUDIO_PITCH_SHIFTER_HPP

#include "HannOscillator.hpp"
#include "Phasor.hpp"
#include "Processable.hpp"
#include "TapDelayCubic.hpp"
#include "types.hpp"
#include "utility.hpp"
#include <array>
#include <cstdint>

namespace md_audio {

    template <std::uint16_t OVERLAP = 2, typename Delay = TapDelayCubic<OVERLAP>>
    class PitchShifter : public Processable<MdFloat, MdFloat> {
    public:
        static_assert(OVERLAP > 1, "Overlap factor must be at least 2!");

        explicit PitchShifter(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat);

        explicit PitchShifter(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat, MdFloat);

        void initialise();

        inline void set_transposition(MdFloat) noexcept;

        void set_size(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        Delay m_delay;
        std::array<Phasor, OVERLAP> m_phasor;
        std::array<HannOscillator, OVERLAP> m_osc;
        MdFloat m_transposition = 0;
        MdFloat m_size;
        const MdFloat norm = static_cast<MdFloat>(2) / OVERLAP;

        void initialise(MdFloat, MdFloat);

        void set_frequency() noexcept;

        inline MdFloat check_transposition(MdFloat) noexcept;

        inline MdFloat check_size(MdFloat) noexcept;

        inline static constexpr MdFloat compute_frequency(MdFloat, MdFloat) noexcept;
    };

    template <std::uint16_t OVERLAP, typename Delay>
    PitchShifter<OVERLAP, Delay>::PitchShifter(memory::Allocatable<MdFloat*>& allocator,
        MdFloat max_delay, MdFloat size) :
        m_delay(allocator, max_delay)
    {
        initialise(size, static_cast<MdFloat>(1));
    }

    template <std::uint16_t OVERLAP, typename Delay>
    PitchShifter<OVERLAP, Delay>::PitchShifter(memory::Allocatable<MdFloat*>& allocator,
        MdFloat max_delay, MdFloat size, MdFloat transposition) :
        m_delay(allocator, max_delay)
    {
        initialise(size, transposition);
    }

    template <std::uint16_t OVERLAP, typename Delay>
    void PitchShifter<OVERLAP, Delay>::initialise() {
        m_delay.initialise();
    }

    template <std::uint16_t OVERLAP, typename Delay>
    void PitchShifter<OVERLAP, Delay>::initialise(MdFloat size, MdFloat transposition) {
        m_size = check_size(size);
        m_transposition = check_transposition(transposition);

        set_frequency();

        for (auto i = 0; i < OVERLAP; i++)
            m_phasor[i].set_phase(
                static_cast<MdFloat>(1) - static_cast<MdFloat>(i) / static_cast<MdFloat>(OVERLAP)
            );
    }

    template <std::uint16_t OVERLAP, typename Delay>
    void PitchShifter<OVERLAP, Delay>::set_transposition(MdFloat transposition) noexcept {
        m_transposition = check_transposition(transposition);

        set_frequency();
    }

    template <std::uint16_t OVERLAP, typename Delay>
    void PitchShifter<OVERLAP, Delay>::set_size(MdFloat size) noexcept {
        m_size = check_size(size);

        set_frequency();
    }

    template <std::uint16_t OVERLAP, typename Delay>
    void PitchShifter<OVERLAP, Delay>::set_frequency() noexcept {
        auto frequency = compute_frequency(m_transposition, m_size);

        for (auto& p : m_phasor)
            p.set_frequency(frequency);
    }

    template <std::uint16_t OVERLAP, typename Delay>
    MdFloat PitchShifter<OVERLAP, Delay>::check_transposition(MdFloat transposition) noexcept {
        return utility::clip(
            transposition, static_cast<MdFloat>(-24), static_cast<MdFloat>(24)
        );
    }

    template <std::uint16_t OVERLAP, typename Delay>
    MdFloat PitchShifter<OVERLAP, Delay>::check_size(MdFloat size) noexcept {
        return utility::clip(size, static_cast<MdFloat>(5), m_delay.get_max_delay());
    }

    template <std::uint16_t OVERLAP, typename Delay>
    MdFloat PitchShifter<OVERLAP, Delay>::perform(MdFloat in) noexcept {
        auto z = static_cast<MdFloat>(0);
        auto window = std::array<MdFloat, OVERLAP>{};

        for (auto i = 0; i < OVERLAP; i++) {
            auto phase = m_phasor[i].perform();

            m_osc[i].set_phase(static_cast<MdFloat>(phase * two_pi));

            auto window = m_osc[i].perform();

            m_delay.set_delay(i, phase * m_size);

            z += m_delay.read(i) * window;
        }

        m_delay.write(in); // Write the next sample to the delay buffer

        return z * norm;
    }

    template <std::uint16_t OVERLAP, typename Delay>
    constexpr MdFloat PitchShifter<OVERLAP, Delay>::compute_frequency(MdFloat transposition, MdFloat size) noexcept {
        return -(utility::midi_ratio(transposition) - static_cast<MdFloat>(1))
            * static_cast<MdFloat>(sample_rate) / size;
    }

}

#endif /* MD_AUDIO_PITCH_SHIFTER_HPP */
