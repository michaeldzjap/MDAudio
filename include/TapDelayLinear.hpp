#ifndef MD_AUDIO_TAP_DELAY_LINEAR_HPP
#define MD_AUDIO_TAP_DELAY_LINEAR_HPP

#include "TapDelayInterp.hpp"

namespace md_audio {

    template <typename Allocator, std::size_t taps>
    class TapDelayLinear : public TapDelayInterp<Allocator, taps> {
    public:
        explicit TapDelayLinear(Allocator&, MdFloat);

        explicit TapDelayLinear(Allocator&, MdFloat, const std::array<MdFloat, taps>&);

        inline MdFloat get_max_delay() noexcept override final;

        MdFloat read(std::size_t) noexcept override final;
    };

    template <typename Allocator, std::size_t taps>
    TapDelayLinear<Allocator, taps>::TapDelayLinear(Allocator& allocator, MdFloat max_delay) :
        TapDelayInterp<Allocator, taps>(allocator, max_delay)
    {}

    template <typename Allocator, std::size_t taps>
    TapDelayLinear<Allocator, taps>::TapDelayLinear(Allocator& allocator, MdFloat max_delay,
        const std::array<MdFloat, taps>& delay) :
        TapDelayInterp<Allocator, taps>(allocator, max_delay)
    {
        this->set_delay(delay);
    }

    template <typename Allocator, std::size_t taps>
    MdFloat TapDelayLinear<Allocator, taps>::get_max_delay() noexcept {
        return this->m_max_delay - 1;
    }

    template <typename Allocator, std::size_t taps>
    MdFloat TapDelayLinear<Allocator, taps>::read(std::size_t index) noexcept {
        auto phase_a = utility::wrap(this->m_write_index - this->m_delay[index], 0, this->m_upper_bound_1);
        auto phase_b = utility::wrap(phase_a - 1, 0, this->m_upper_bound_1);

        auto d1 = this->m_buffer[phase_a];
        auto d2 = this->m_buffer[phase_b];

        return utility::linear_interp(this->m_frac[index], d1, d2);
    }

}

#endif /* MD_AUDIO_TAP_DELAY_LINEAR_HPP */
