#ifndef MD_AUDIO_REVERB_HPP
#define MD_AUDIO_REVERB_HPP

#include "Allocatable.hpp"
#include "AllpassStatic.hpp"
#include "HighpassFirstOrder.hpp"
#include "HighshelfFirstOrder.hpp"
#include "LowpassFirstOrder.hpp"
#include "LowshelfFirstOrder.hpp"
#include "PitchShifter.hpp"
#include "Processable.hpp"
#include "ReverbConfig.hpp"
#include "ReversibleDelay.hpp"
#include "SineShaper.hpp"
#include "TapDelayCubic.hpp"
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

        void set_shimmer(MdFloat) noexcept;

        void set_tilt(MdFloat) noexcept;

        void set_mix(MdFloat) noexcept;

        std::array<MdFloat, ReverbConfig::number_of_outputs> perform(MdFloat) noexcept override final;

    private:
        ReversibleDelay<2> m_pre_delay;
        std::array<AllpassStatic, ReverbConfig::number_of_delays> m_allpass;
        std::array<TapDelayCubic<ReverbConfig::number_of_taps>, ReverbConfig::number_of_delays> m_delay;
        std::array<std::array<MdFloat, ReverbConfig::number_of_taps>, ReverbConfig::number_of_delays> m_delay_times;
        std::array<LowpassFirstOrder, ReverbConfig::number_of_delays> m_lowpass;
        std::array<LowpassFirstOrder, ReverbConfig::number_of_outputs> m_lowpass_shifter;
        std::array<HighpassFirstOrder, ReverbConfig::number_of_delays> m_highpass;
        std::array<SineShaper, ReverbConfig::number_of_delays> m_shaper;
        std::array<PitchShifter<2>, ReverbConfig::number_of_outputs> m_shifter;
        std::array<LowshelfFirstOrder, ReverbConfig::number_of_outputs> m_lowshelf;
        std::array<HighshelfFirstOrder, ReverbConfig::number_of_outputs> m_highshelf;
        std::array<MdFloat, ReverbConfig::number_of_delays> m_feedback{};
        MdFloat m_decay;
        MdFloat m_shimmer;
        MdFloat m_dry;
        MdFloat m_wet;
    };

}

#endif /* MD_AUDIO_REVERB_HPP */
