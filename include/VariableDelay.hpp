#ifndef MD_AUDIO_VARIABLE_DELAY
#define MD_AUDIO_VARIABLE_DELAY

#include "HannOscillator.hpp"
#include "Latch.hpp"
#include "Phasor.hpp"
#include "Processable.hpp"
#include "TapDelayStatic.hpp"

namespace md_audio {

    template <std::uint16_t OVERLAP = 4>
    class VariableDelay : public Processable<MdFloat, MdFloat> {
    public:
        static_assert(OVERLAP > 1, "Overlap factor must be at least 2!");

        explicit VariableDelay(memory::Allocatable<MdFloat*>&, MdFloat);

        explicit VariableDelay(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat);

        explicit VariableDelay(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat, MdFloat);

        void initialise();

        inline void set_delay(MdFloat) noexcept;

        void set_size(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        TapDelayStatic<OVERLAP> m_delay;
        std::array<Phasor, OVERLAP> m_phasor;
        std::array<HannOscillator, OVERLAP> m_osc;
        std::array<Latch, OVERLAP> m_latch;
        MdFloat m_delay_samples;
        const MdFloat m_norm = static_cast<MdFloat>(2) / OVERLAP;

        void initialise(MdFloat, MdFloat) noexcept;

        inline static constexpr MdFloat compute_frequency(MdFloat) noexcept;
    };

    template <std::uint16_t OVERLAP>
    VariableDelay<OVERLAP>::VariableDelay(memory::Allocatable<MdFloat*>& allocator,
        MdFloat max_delay) :
        m_delay(allocator, max_delay)
    {
        initialise(static_cast<MdFloat>(1), static_cast<MdFloat>(1));
    }

    template <std::uint16_t OVERLAP>
    VariableDelay<OVERLAP>::VariableDelay(memory::Allocatable<MdFloat*>& allocator,
        MdFloat max_delay, MdFloat delay) :
        m_delay(allocator, max_delay)
    {
        initialise(delay, static_cast<MdFloat>(1));
    }

    template <std::uint16_t OVERLAP>
    VariableDelay<OVERLAP>::VariableDelay(memory::Allocatable<MdFloat*>& allocator,
        MdFloat max_delay, MdFloat delay, MdFloat size) :
        m_delay(allocator, max_delay)
    {
        initialise(delay, size);
    }

    template <std::uint16_t OVERLAP>
    void VariableDelay<OVERLAP>::initialise() {
        m_delay.initialise();
    }

    template <std::uint16_t OVERLAP>
    void VariableDelay<OVERLAP>::initialise(MdFloat delay, MdFloat size) noexcept {
        set_delay(delay);
        set_size(size);

        for (auto i = 0; i < OVERLAP; i++)
            m_phasor[i].set_phase(static_cast<MdFloat>(i) / static_cast<MdFloat>(OVERLAP));
    }

    template <std::uint16_t OVERLAP>
    void VariableDelay<OVERLAP>::set_delay(MdFloat delay) noexcept {
        m_delay_samples = utility::clip(delay, static_cast<MdFloat>(5), m_delay.get_max_delay());;
    }

    template <std::uint16_t OVERLAP>
    void VariableDelay<OVERLAP>::set_size(MdFloat size) noexcept {
        size = utility::clip(size, static_cast<MdFloat>(5), m_delay.get_max_delay());

        auto frequency = compute_frequency(size);

        for (auto& p : m_phasor)
            p.set_frequency(frequency);
    }

    template <std::uint16_t OVERLAP>
    MdFloat VariableDelay<OVERLAP>::perform(MdFloat in) noexcept {
        auto z = static_cast<MdFloat>(0);

        for (auto i = 0; i < OVERLAP; i++) {
            auto phase = m_phasor[i].perform();

            m_osc[i].set_phase(static_cast<MdFloat>(phase * two_pi));

            auto window = m_osc[i].perform();
            auto delay = m_latch[i].perform(m_delay_samples, phase);

            m_delay.set_delay(i, delay);

            z += m_delay.read(i) * window;
        }

        m_delay.write(in); // Write the next sample to the delay buffer

        return z * m_norm;
    }

    template <std::uint16_t OVERLAP>
    constexpr MdFloat VariableDelay<OVERLAP>::compute_frequency(MdFloat size) noexcept {
        return static_cast<MdFloat>(sample_rate) / size;
    }

}

#endif /* MD_AUDIO_VARIABLE_DELAY */
