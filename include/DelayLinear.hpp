#ifndef MD_AUDIO_DELAY_LINEAR_HPP
#define MD_AUDIO_DELAY_LINEAR_HPP

#include "DelayInterp.hpp"

namespace md_audio {

    template <typename Allocator>
    class DelayLinear : public DelayInterp<Allocator> {
    public:
        explicit DelayLinear(Allocator&, MdFloat, MdFloat);

        inline MdFloat get_max_delay() noexcept override final;

        MdFloat read() noexcept override final;
    };

    template <typename Allocator>
    DelayLinear<Allocator>::DelayLinear(Allocator& allocator, MdFloat max_delay, MdFloat delay) :
        DelayInterp<Allocator>(allocator, max_delay)
    {
        this->set_delay(delay);
    }

    template <typename Allocator>
    MdFloat DelayLinear<Allocator>::get_max_delay() noexcept {
        return this->m_max_delay - 1;
    }

    template <typename Allocator>
    MdFloat DelayLinear<Allocator>::read() noexcept {
        // Get the correct read positions into the buffer
        auto phase_a = utility::wrap(this->m_write_index - this->m_delay, 0, this->m_upper_bound_1);
        auto phase_b = utility::wrap(phase_a - 1, 0, this->m_upper_bound_1);

        auto d1 = this->m_buffer[phase_a];
        auto d2 = this->m_buffer[phase_b];

        return utility::linear_interp(this->m_frac, d1, d2);
    }

}

#endif /* MD_AUDIO_DELAY_LINEAR_HPP */
