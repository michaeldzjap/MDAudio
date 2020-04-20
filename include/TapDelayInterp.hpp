#ifndef MD_AUDIO_TAP_DELAY_INTERP_HPP
#define MD_AUDIO_TAP_DELAY_INTERP_HPP

#include "TapDelay.hpp"
#include "types.hpp"
#include "utility.hpp"
#include <array>

namespace md_audio {

    template <std::size_t taps>
    class TapDelayInterp : public TapDelay<taps> {
    public:
        explicit TapDelayInterp(memory::Allocatable<MdFloat*>&, MdFloat);

        using TapDelay<taps>::set_delay;

        inline void set_delay(std::size_t, MdFloat) noexcept override final;

        virtual ~TapDelayInterp() = 0;

    protected:
        std::array<MdFloat, taps> m_frac;
    };

    template <std::size_t taps>
    TapDelayInterp<taps>::TapDelayInterp(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay) :
        TapDelay<taps>(allocator, max_delay)
    {}

    template <std::size_t taps>
    void TapDelayInterp<taps>::set_delay(std::size_t i, MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), this->get_max_delay());

        this->m_delay[i] = static_cast<std::uint32_t>(delay);

        m_frac[i] = delay - static_cast<MdFloat>(this->m_delay[i]);
    }

    template <std::size_t taps>
    TapDelayInterp<taps>::~TapDelayInterp() {}

}

#endif /* MD_AUDIO_TAP_DELAY_INTERP_HPP */
