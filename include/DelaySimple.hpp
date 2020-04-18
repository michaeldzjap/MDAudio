#ifndef MD_AUDIO_DELAY_SIMPLE_HPP
#define MD_AUDIO_DELAY_SIMPLE_HPP

#include "Delay.hpp"

namespace md_audio {

    template <typename Allocator>
    class DelaySimple : public Delay<Allocator> {
    public:
        explicit DelaySimple(Allocator&, MdFloat, MdFloat);

        inline void set_delay(MdFloat) noexcept override final;

        inline MdFloat get_max_delay() noexcept override final;

        MdFloat read() noexcept override final;
    };

    template <typename Allocator>
    DelaySimple<Allocator>::DelaySimple(Allocator& allocator, MdFloat max_delay, MdFloat delay) :
        Delay<Allocator>(allocator, max_delay)
    {
        set_delay(delay);
    }

    template <typename Allocator>
    void DelaySimple<Allocator>::set_delay(MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), get_max_delay());

        this->m_delay = static_cast<std::uint32_t>(delay);
    }

    template <typename Allocator>
    MdFloat DelaySimple<Allocator>::get_max_delay() noexcept {
        return this->m_max_delay;
    }

    template <typename Allocator>
    MdFloat DelaySimple<Allocator>::read() noexcept {
        // Get the correct read position into the buffer
        auto phase = utility::wrap(this->m_write_index - this->m_delay, 0, this->m_upper_bound_1);

        return this->m_buffer[phase];
    }

}

#endif /* MD_AUDIO_DELAY_SIMPLE_HPP */
