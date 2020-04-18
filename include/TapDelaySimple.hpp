#ifndef MD_AUDIO_TAP_DELAY_SIMPLE_HPP
#define MD_AUDIO_TAP_DELAY_SIMPLE_HPP

#include "TapDelay.hpp"

namespace md_audio {

    template <typename Allocator, std::size_t taps>
    class TapDelaySimple : public TapDelay<Allocator, taps> {
    public:
        explicit TapDelaySimple(Allocator&, MdFloat);

        explicit TapDelaySimple(Allocator&, MdFloat, const std::array<MdFloat, taps>&);

        using TapDelay<Allocator, taps>::set_delay;

        inline void set_delay(std::size_t, MdFloat) noexcept override final;

        inline MdFloat get_max_delay() noexcept override final;

        MdFloat read(std::size_t) noexcept override final;
    };

    template <typename Allocator, std::size_t taps>
    TapDelaySimple<Allocator, taps>::TapDelaySimple(Allocator& allocator, MdFloat max_delay) :
        TapDelay<Allocator, taps>(allocator, max_delay)
    {}

    template <typename Allocator, std::size_t taps>
    TapDelaySimple<Allocator, taps>::TapDelaySimple(Allocator& allocator, MdFloat max_delay,
        const std::array<MdFloat, taps>& delay) :
        TapDelay<Allocator, taps>(allocator, max_delay)
    {
        this->set_delay(delay);
    }

    template <typename Allocator, std::size_t taps>
    void TapDelaySimple<Allocator, taps>::set_delay(std::size_t i, MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), get_max_delay());

        this->m_delay[i] = static_cast<std::uint32_t>(delay);
    }

    template <typename Allocator, std::size_t taps>
    MdFloat TapDelaySimple<Allocator, taps>::get_max_delay() noexcept {
        return this->m_max_delay;
    }

    template <typename Allocator, std::size_t taps>
    MdFloat TapDelaySimple<Allocator, taps>::read(std::size_t index) noexcept {
        auto phase = utility::wrap(this->m_write_index - this->m_delay[index], 0, this->m_upper_bound_1);

        return this->m_buffer[phase];
    }

}

#endif /* MD_AUDIO_TAP_DELAY_SIMPLE_HPP */
