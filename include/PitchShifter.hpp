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

    template <
        typename Allocator,
        std::size_t overlap = 2,
        typename Delay = TapDelayCubic<Allocator, overlap>
    >
    class PitchShifter : public Processable<MdFloat, MdFloat> {
    public:
        static_assert(overlap > 1, "Overlap factor must be at least 2!");

        explicit PitchShifter(Allocator&, MdFloat, MdFloat);

        explicit PitchShifter(Allocator&, MdFloat, MdFloat, MdFloat);

        void initialise();

        void set_transposition(MdFloat) noexcept;

        void set_size(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        Delay m_delay;
        std::array<Phasor, overlap> m_phasor;
        std::array<HannOscillator, overlap> m_osc;
        MdFloat m_transposition = 0;
        MdFloat m_size;
        const MdFloat norm = static_cast<MdFloat>(2) / overlap;

        void initialise(MdFloat, MdFloat);

        void set_frequency() noexcept;

        MdFloat check_transposition(MdFloat) noexcept;

        MdFloat check_size(MdFloat) noexcept;

        static constexpr MdFloat compute_frequency(MdFloat, MdFloat) noexcept;
    };

    template <typename Allocator, std::size_t overlap, typename Delay>
    PitchShifter<Allocator, overlap, Delay>::PitchShifter(Allocator& allocator, MdFloat max_delay,
        MdFloat size) :
        m_delay(allocator, max_delay)
    {
        initialise(size, static_cast<MdFloat>(1));
    }

    template <typename Allocator, std::size_t overlap, typename Delay>
    PitchShifter<Allocator, overlap, Delay>::PitchShifter(Allocator& allocator, MdFloat max_delay,
        MdFloat size, MdFloat transposition) :
        m_delay(allocator, max_delay)
    {
        initialise(size, transposition);
    }

    template <typename Allocator, std::size_t overlap, typename Delay>
    void PitchShifter<Allocator, overlap, Delay>::initialise() {
        m_delay.initialise();
    }

    template <typename Allocator, std::size_t overlap, typename Delay>
    void PitchShifter<Allocator, overlap, Delay>::initialise(MdFloat size, MdFloat transposition) {
        m_size = check_size(size);
        m_transposition = check_transposition(transposition);

        set_frequency();

        for (auto i = 0; i < overlap; i++)
            m_phasor[i].set_phase(
                static_cast<MdFloat>(1) - static_cast<MdFloat>(i) / static_cast<MdFloat>(overlap)
            );
    }

    template <typename A, std::size_t overlap, typename Delay>
    inline void PitchShifter<A, overlap, Delay>::set_transposition(MdFloat transposition) noexcept {
        m_transposition = check_transposition(transposition);

        set_frequency();
    }

    template <typename A, std::size_t overlap, typename Delay>
    inline void PitchShifter<A, overlap, Delay>::set_size(MdFloat size) noexcept {
        m_size = check_size(size);

        set_frequency();
    }

    template <typename A, std::size_t overlap, typename Delay>
    inline void PitchShifter<A, overlap, Delay>::set_frequency() noexcept {
        auto frequency = compute_frequency(m_transposition, m_size);

        for (auto& p : m_phasor)
            p.set_frequency(frequency);
    }

    template <typename A, std::size_t overlap, typename Delay>
    inline MdFloat PitchShifter<A, overlap, Delay>::check_transposition(MdFloat transposition) noexcept {
        return utility::clip(
            transposition, static_cast<MdFloat>(-24), static_cast<MdFloat>(24)
        );
    }

    template <typename A, std::size_t overlap, typename Delay>
    inline MdFloat PitchShifter<A, overlap, Delay>::check_size(MdFloat _size) noexcept {
        return utility::clip(_size, static_cast<MdFloat>(5), m_delay.get_max_delay());
    }

    template <typename A, std::size_t overlap, typename Delay>
    MdFloat PitchShifter<A, overlap, Delay>::perform(MdFloat in) noexcept {
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

        return z * norm;
    }

    template <typename A, std::size_t overlap, typename Delay>
    inline constexpr MdFloat PitchShifter<A, overlap, Delay>::compute_frequency(MdFloat transposition, MdFloat size) noexcept {
        return -(utility::midi_ratio(transposition) - static_cast<MdFloat>(1))
            * static_cast<MdFloat>(sample_rate) / size;
    }

}

#endif /* MD_AUDIO_PITCH_SHIFTER_HPP */
