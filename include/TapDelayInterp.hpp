#ifndef MD_AUDIO_TAP_DELAY_INTERP_HPP
#define MD_AUDIO_TAP_DELAY_INTERP_HPP

#include "TapDelay.hpp"
#include "types.hpp"
#include "utility.hpp"
#include <array>

namespace md_audio {

    template <typename Allocator, std::size_t taps>
    class TapDelayInterp : public TapDelay<Allocator, taps> {
    public:
        explicit TapDelayInterp(Allocator&, MdFloat);

        using TapDelay<Allocator, taps>::set_delay;

        inline void set_delay(std::size_t, MdFloat) noexcept override final;

        virtual ~TapDelayInterp() = 0;

    protected:
        std::array<MdFloat, taps> m_frac;
    };

    template <typename Allocator, std::size_t taps>
    TapDelayInterp<Allocator, taps>::TapDelayInterp(Allocator& allocator, MdFloat max_delay) :
        TapDelay<Allocator, taps>(allocator, max_delay)
    {}

    template <typename Allocator, std::size_t taps>
    void TapDelayInterp<Allocator, taps>::set_delay(std::size_t i, MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), this->get_max_delay());

        this->m_delay[i] = static_cast<std::uint32_t>(delay);

        m_frac[i] = delay - static_cast<MdFloat>(this->m_delay[i]);
    }

    template <typename Allocator, std::size_t taps>
    TapDelayInterp<Allocator, taps>::~TapDelayInterp() {}

}

#endif /* MD_AUDIO_TAP_DELAY_INTERP_HPP */
