#ifndef MD_AUDIO_REVERB_HPP
#define MD_AUDIO_REVERB_HPP

#include "Allocatable.hpp"
#include "AllpassStatic.hpp"
#include "Buffer.hpp"
#include "HannOscillator.hpp"
#include "HighpassFirstOrder.hpp"
#include "HighshelfFirstOrder.hpp"
#include "LowpassFirstOrder.hpp"
#include "LowshelfFirstOrder.hpp"
#include "PitchShifter.hpp"
#include "Processable.hpp"
#include "Reader.hpp"
#include "ReaderLinear.hpp"
#include "ReverbConfig.hpp"
#include "ReversibleDelay.hpp"
#include "SineOscillator.hpp"
#include "SineShaper.hpp"
#include "TapDelayLinear.hpp"
#include "Writer.hpp"
#include "types.hpp"

namespace md_audio {

    class Reverb : public Processable<std::array<MdFloat, ReverbConfig::number_of_outputs>, MdFloat> {
    public:
        explicit Reverb(memory::Allocatable<MdFloat*>&);

        void initialise();

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

        std::array<MdFloat, ReverbConfig::number_of_outputs> perform(MdFloat) noexcept override final;

    private:
        ReversibleDelay m_pre_delay;
        std::array<AllpassStatic, ReverbConfig::number_of_delays> m_allpass;
        std::array<Buffer, ReverbConfig::number_of_delays> m_buffer;
        std::array<Writer, ReverbConfig::number_of_delays> m_writer;
        std::array<LowpassFirstOrder, ReverbConfig::number_of_delays> m_lowpass;
        std::array<LowpassFirstOrder, ReverbConfig::number_of_outputs> m_lowpass_shifter;
        std::array<HighpassFirstOrder, ReverbConfig::number_of_delays> m_highpass;
        std::array<SineShaper, ReverbConfig::number_of_delays> m_shaper;
        std::array<PitchShifter, ReverbConfig::number_of_outputs> m_shifter;
        std::array<LowshelfFirstOrder, ReverbConfig::number_of_outputs> m_lowshelf;
        std::array<HighshelfFirstOrder, ReverbConfig::number_of_outputs> m_highshelf;
        std::array<std::array<HannOscillator, ReverbConfig::overlap_ergodic>, ReverbConfig::number_of_delays> m_window;
        std::array<std::array<SineOscillator, ReverbConfig::serial_periodic>, ReverbConfig::number_of_delays> m_osc;
        std::array<std::array<Reader, ReverbConfig::early_reflections>, ReverbConfig::number_of_delays> m_early_reader;
        std::array<std::array<Reader, ReverbConfig::overlap_ergodic>, ReverbConfig::number_of_delays> m_late_ergodic_reader;
        std::array<std::array<ReaderLinear, ReverbConfig::serial_periodic>, ReverbConfig::number_of_delays> m_late_periodic_reader;
        std::array<MdFloat, ReverbConfig::number_of_delays> m_late_delay;
        std::array<std::array<MdFloat, ReverbConfig::early_reflections>, ReverbConfig::number_of_delays> m_early_delay;
        std::array<MdFloat, ReverbConfig::number_of_delays> m_feedback{};
        MdFloat m_decay;
        MdFloat m_shimmer;
        MdFloat m_ergodic_depth;
        MdFloat m_periodic_depth;
        MdFloat m_dry;
        MdFloat m_wet;
    };

}

#endif /* MD_AUDIO_REVERB_HPP */
