#ifndef MD_AUDIO_REVERB_HPP
#define MD_AUDIO_REVERB_HPP

#include "AllpassStatic.hpp"
#include "Buffer.hpp"
#include "HannOscillator.hpp"
#include "HighpassFirstOrder.hpp"
#include "HighshelfFirstOrder.hpp"
#include "Latch.hpp"
#include "LowpassFirstOrder.hpp"
#include "LowshelfFirstOrder.hpp"
#include "Normaliser.hpp"
#include "Phasor.hpp"
#include "PitchShifter.hpp"
#include "Reader.hpp"
#include "ReaderLinear.hpp"
#include "ReverbConfig.hpp"
#include "ReversibleDelay.hpp"
#include "SampleRate.hpp"
#include "SineOscillator.hpp"
#include "SineShaper.hpp"
#include "TapDelayLinear.hpp"
#include "WhiteNoise.hpp"
#include "Writer.hpp"
#include "interfaces/Processable.hpp"
#include "types.hpp"
#include "utility.hpp"

namespace md_audio {

    /**
     * A feedback delay network reverb that attempts to emulate the Erbe-Verb.
     * No idea if it even comes close to it to be honest, but it sounds pretty
     * damn awesome in its own way.
     */
    class Reverb :
        public SampleRate,
        public Processable<std::array<MdFloat, ReverbConfig::output_count>, MdFloat>
    {
    public:
        explicit Reverb(memory::Poolable&);

        void set_size(MdFloat) noexcept;

        void set_decay(MdFloat) noexcept;

        void set_absorb(MdFloat) noexcept;

        void set_pre_delay(MdFloat) noexcept;

        void set_reverse(bool) noexcept;

        void set_modulation_rate(MdFloat) noexcept;

        void set_modulation_depth(MdFloat) noexcept;

        void set_shimmer(MdFloat) noexcept;

        void set_tilt(MdFloat) noexcept;

        void set_mix(MdFloat) noexcept;

        std::array<MdFloat, ReverbConfig::output_count> perform(MdFloat) noexcept override final;

    private:
        static std::array<MdFloat, ReverbConfig::delay_count> m_max_delay_samples;
        ReversibleDelay m_pre_delay;
        std::array<AllpassStatic, ReverbConfig::delay_count> m_allpass;
        std::array<LowpassFirstOrder, ReverbConfig::delay_count> m_lowpass;
        std::array<LowpassFirstOrder, ReverbConfig::output_count> m_lowpass_shifter;
        std::array<HighpassFirstOrder, ReverbConfig::delay_count> m_highpass;
        std::array<SineShaper, ReverbConfig::delay_count> m_shaper;
        std::array<Phasor, ReverbConfig::modulation_stages> m_phasor;
        std::array<Latch, ReverbConfig::modulation_stages> m_latch;
        WhiteNoise m_noise;
        std::array<HannOscillator, ReverbConfig::modulation_stages> m_hann;
        std::array<SineOscillator, ReverbConfig::modulation_stages> m_sine;
        std::array<std::array<Buffer, ReverbConfig::delay_count>, ReverbConfig::serial_stages> m_buffer;
        std::array<std::array<Writer, ReverbConfig::delay_count>, ReverbConfig::serial_stages> m_writer;
        std::array<Reader, ReverbConfig::delay_count> m_early_reader;
        std::array<std::array<ReaderLinear, ReverbConfig::delay_count>, ReverbConfig::serial_stages> m_late_reader;
        std::array<Normaliser, ReverbConfig::delay_count> m_normaliser;
        std::array<PitchShifter, ReverbConfig::output_count> m_shifter;
        std::array<LowshelfFirstOrder, ReverbConfig::output_count> m_lowshelf;
        std::array<HighshelfFirstOrder, ReverbConfig::output_count> m_highshelf;
        std::array<MdFloat, ReverbConfig::delay_count> m_late_delay;
        std::array<std::array<MdFloat, ReverbConfig::output_count>, ReverbConfig::delay_count> m_early_delay;
        std::array<MdFloat, ReverbConfig::delay_count> m_feedback{};
        MdFloat m_decay;
        MdFloat m_shimmer;
        MdFloat m_ergodic_depth;
        MdFloat m_periodic_depth;
        MdFloat m_dry;
        MdFloat m_wet;
    };

}

#endif /* MD_AUDIO_REVERB_HPP */
