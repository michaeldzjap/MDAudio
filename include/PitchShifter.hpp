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

        static void set_sample_rate(double) noexcept;

        ~PitchShifter();

    private:
        const MdFloat m_max_size;
        MdFloat m_transposition = static_cast<MdFloat>(0);
        MdFloat m_size;
        const std::size_t m_overlap;
        const MdFloat m_norm;
        memory::Poolable& m_pool;
        TapDelayLinear m_delay;
        Phasor* m_phasor = nullptr;
        HannOscillator* m_osc = nullptr;

        void initialise(MdFloat, MdFloat);

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
        return utility::clip<MdFloat>(transposition, -24, 24);
    }

    MdFloat PitchShifter::check_size(MdFloat size) noexcept {
        return utility::clip<MdFloat>(size, .01, m_max_size);
    }

    constexpr MdFloat PitchShifter::compute_frequency(MdFloat transposition, MdFloat size) noexcept {
        return -(utility::midi_ratio(transposition) - static_cast<MdFloat>(1)) / size;
    }

}

#endif /* MD_AUDIO_PITCH_SHIFTER_HPP */
