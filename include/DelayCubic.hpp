#ifndef MD_AUDIO_DELAY_CUBIC_HPP
#define MD_AUDIO_DELAY_CUBIC_HPP

#include "DelayInterp.hpp"

namespace md_audio {

    template <typename Allocator>
    class DelayCubic : public DelayInterp<Allocator> {
    public:
        explicit DelayCubic(Allocator&, MdFloat, MdFloat);

        inline MdFloat get_max_delay() noexcept override final;

        MdFloat read() noexcept override final;
    };

    template <typename Allocator>
    DelayCubic<Allocator>::DelayCubic(Allocator& allocator, MdFloat max_delay, MdFloat delay) :
        DelayInterp<Allocator>(allocator, max_delay)
    {
        this->set_delay(delay);
    }

    template <typename Allocator>
    MdFloat DelayCubic<Allocator>::get_max_delay() noexcept {
        return this->m_max_delay - 2;
    }

    template <typename Allocator>
    MdFloat DelayCubic<Allocator>::read() noexcept {
        // Get the correct read positions into the buffer
        auto phase_1 = utility::wrap(this->m_write_index - this->m_delay, 0, this->m_upper_bound_1);
        auto phase_2 = utility::wrap(phase_1 - 1, 0, this->m_upper_bound_1);
        auto phase_3 = utility::wrap(phase_1 - 2, 0, this->m_upper_bound_1);
        auto phase_0 = utility::wrap(phase_1 + 1, 0, this->m_upper_bound_1);

        auto d0 = this->m_buffer[phase_0];
        auto d1 = this->m_buffer[phase_1];
        auto d2 = this->m_buffer[phase_2];
        auto d3 = this->m_buffer[phase_3];

        return utility::cubic_interp(this->m_frac, d0, d1, d2, d3);
    }

}

#endif /* MD_AUDIO_DELAY_CUBIC_HPP */
