#ifndef MD_AUDIO_PITCH_SHIFTER_HPP
#define MD_AUDIO_PITCH_SHIFTER_HPP

#include "HannOscillator.hpp"
#include "InterpolationType.hpp"
#include "Phasor.hpp"
#include "TapDelay.hpp"
#include "interfaces/Processable.hpp"
#include "types.hpp"

namespace md_audio {

    class PitchShifter : public Processable<MdFloat, MdFloat> {
    public:
        explicit PitchShifter(memory::Poolable&, std::size_t, MdFloat, std::size_t, InterpolationType = InterpolationType::linear);

        explicit PitchShifter(memory::Poolable&, std::size_t, MdFloat, MdFloat, std::size_t, InterpolationType = InterpolationType::linear);

        inline void set_transposition(MdFloat) noexcept;

        void set_size(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

        ~PitchShifter();

    private:
        memory::Poolable& m_pool;
        TapDelay m_delay;
        Phasor* m_phasor = nullptr;
        HannOscillator* m_osc = nullptr;
        MdFloat m_transposition = 0;
        MdFloat m_size;
        std::size_t m_overlap;
        const MdFloat m_norm;

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
        return utility::clip(size, static_cast<MdFloat>(5), m_delay.get_max_delay());
    }

    constexpr MdFloat PitchShifter::compute_frequency(MdFloat transposition, MdFloat size) noexcept {
        return -(utility::midi_ratio(transposition) - static_cast<MdFloat>(1))
            * static_cast<MdFloat>(sample_rate) / size;
    }

}

#endif /* MD_AUDIO_PITCH_SHIFTER_HPP */
