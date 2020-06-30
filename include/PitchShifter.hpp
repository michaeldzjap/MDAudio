#ifndef MD_AUDIO_PITCH_SHIFTER_HPP
#define MD_AUDIO_PITCH_SHIFTER_HPP

#include "HannOscillator.hpp"
#include "Phasor.hpp"
#include "TapDelayLinear.hpp"
#include "interfaces/Processable.hpp"
#include "types.hpp"

namespace md_audio {

    class PitchShifter : public Processable<MdFloat, MdFloat> {
    public:
        explicit PitchShifter(memory::Poolable&, MdFloat, MdFloat, std::size_t);

        explicit PitchShifter(memory::Poolable&, MdFloat, MdFloat, MdFloat, std::size_t);

        inline void set_transposition(MdFloat) noexcept;

        void set_size(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

        ~PitchShifter();

    private:
        MdFloat m_max_size;
        MdFloat m_transposition = static_cast<MdFloat>(0);
        MdFloat m_size;
        std::size_t m_overlap;
        const MdFloat m_norm;
        memory::Poolable& m_pool;
        TapDelayLinear m_delay;
        Phasor* m_phasor = nullptr;
        HannOscillator* m_osc = nullptr;

        void initialise(MdFloat, MdFloat);

        void* allocate(std::size_t size);

        void set_frequency() noexcept;

        inline MdFloat check_transposition(MdFloat) noexcept;

        inline MdFloat check_size(MdFloat) noexcept;

        inline static constexpr MdFloat compute_frequency(MdFloat, MdFloat) noexcept;
    };

    void PitchShifter::set_transposition(MdFloat transposition) noexcept {
        m_transposition = check_transposition(transposition);

        set_frequency();
    }

    MdFloat PitchShifter::check_transposition(MdFloat transposition) noexcept {
        return utility::clip(
            transposition, static_cast<MdFloat>(-24), static_cast<MdFloat>(24)
        );
    }

    MdFloat PitchShifter::check_size(MdFloat size) noexcept {
        return utility::clip(size, static_cast<MdFloat>(.01), m_max_size);
    }

    constexpr MdFloat PitchShifter::compute_frequency(MdFloat transposition, MdFloat size) noexcept {
        return -(utility::midi_ratio(transposition) - static_cast<MdFloat>(1)) / size;
    }

}

#endif /* MD_AUDIO_PITCH_SHIFTER_HPP */
