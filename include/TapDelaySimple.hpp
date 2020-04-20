#ifndef MD_AUDIO_TAP_DELAY_SIMPLE_HPP
#define MD_AUDIO_TAP_DELAY_SIMPLE_HPP

#include "TapDelay.hpp"

namespace md_audio {

    template <std::size_t taps>
    class TapDelaySimple : public TapDelay<taps> {
    public:
        explicit TapDelaySimple(memory::Allocatable<MdFloat*>&, MdFloat);

        explicit TapDelaySimple(memory::Allocatable<MdFloat*>&, MdFloat, const std::array<MdFloat, taps>&);

        using TapDelay<taps>::set_delay;

        inline void set_delay(std::size_t, MdFloat) noexcept override final;

        inline MdFloat get_max_delay() noexcept override final;

        MdFloat read(std::size_t) noexcept override final;
    };

    template <std::size_t taps>
    TapDelaySimple<taps>::TapDelaySimple(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay) :
        TapDelay<taps>(allocator, max_delay)
    {}

    template <std::size_t taps>
    TapDelaySimple<taps>::TapDelaySimple(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay,
        const std::array<MdFloat, taps>& delay) :
        TapDelay<taps>(allocator, max_delay)
    {
        this->set_delay(delay);
    }

    template <std::size_t taps>
    void TapDelaySimple<taps>::set_delay(std::size_t i, MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), get_max_delay());

        this->m_delay[i] = static_cast<std::uint32_t>(delay);
    }

    template <std::size_t taps>
    MdFloat TapDelaySimple<taps>::get_max_delay() noexcept {
        return this->m_max_delay;
    }

    template <std::size_t taps>
    MdFloat TapDelaySimple<taps>::read(std::size_t index) noexcept {
        auto phase = utility::wrap(
            this->m_write_index - this->m_delay[index], 0, this->m_upper_bound_1
        );

        return this->m_buffer[phase];
    }

}

#endif /* MD_AUDIO_TAP_DELAY_SIMPLE_HPP */
