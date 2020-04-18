#ifndef MD_AUDIO_TAP_DELAY_CUBIC_HPP
#define MD_AUDIO_TAP_DELAY_CUBIC_HPP

#include "TapDelayInterp.hpp"

namespace md_audio {

    template <typename Allocator, std::size_t taps>
    class TapDelayCubic : public TapDelayInterp<Allocator, taps> {
    public:
        explicit TapDelayCubic(Allocator&, MdFloat);

        explicit TapDelayCubic(Allocator&, MdFloat, const std::array<MdFloat, taps>&);

        inline MdFloat get_max_delay() noexcept override final;

        MdFloat read(std::size_t) noexcept override final;
    };

    template <typename Allocator, std::size_t taps>
    TapDelayCubic<Allocator, taps>::TapDelayCubic(Allocator& allocator, MdFloat max_delay) :
        TapDelayInterp<Allocator, taps>(allocator, max_delay)
    {}

    template <typename Allocator, std::size_t taps>
    TapDelayCubic<Allocator, taps>::TapDelayCubic(Allocator& allocator, MdFloat max_delay,
        const std::array<MdFloat, taps>& delay) :
        TapDelayInterp<Allocator, taps>(allocator, max_delay)
    {
        this->set_delay(delay);
    }

    template <typename Allocator, std::size_t taps>
    MdFloat TapDelayCubic<Allocator, taps>::get_max_delay() noexcept {
        return this->m_max_delay - 2;
    }

    template <typename Allocator, std::size_t taps>
    MdFloat TapDelayCubic<Allocator, taps>::read(std::size_t index) noexcept {
        auto phase_1 = utility::wrap(this->m_write_index - this->m_delay[index], 0, this->m_upper_bound_1);
        auto phase_2 = utility::wrap(phase_1 - 1, 0, this->m_upper_bound_1);
        auto phase_3 = utility::wrap(phase_1 - 2, 0, this->m_upper_bound_1);
        auto phase_0 = utility::wrap(phase_1 + 1, 0, this->m_upper_bound_1);

        auto d0 = this->m_buffer[phase_0];
        auto d1 = this->m_buffer[phase_1];
        auto d2 = this->m_buffer[phase_2];
        auto d3 = this->m_buffer[phase_3];

        return utility::cubic_interp(this->m_frac[index], d0, d1, d2, d3);
    }

}

#endif /* MD_AUDIO_TAP_DELAY_CUBIC_HPP */
