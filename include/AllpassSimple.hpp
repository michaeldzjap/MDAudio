#ifndef MD_AUDIO_ALLPASS_SIMPLE_HPP
#define MD_AUDIO_ALLPASS_SIMPLE_HPP

#include "Allpass.hpp"
#include "Processable.hpp"

namespace md_audio {

    template <typename Allocator>
    class AllpassSimple : public Processable<MdFloat, MdFloat>, public Allpass<Allocator> {
    public:
        explicit AllpassSimple(Allocator&, MdFloat, MdFloat);

        explicit AllpassSimple(Allocator&, MdFloat, MdFloat, MdFloat);

        inline void set_delay(MdFloat) noexcept override final;

        MdFloat perform(MdFloat) noexcept override final;
    };

    template <typename Allocator>
    AllpassSimple<Allocator>::AllpassSimple(Allocator& allocator, MdFloat max_delay, MdFloat delay) :
        Allpass<Allocator>(allocator, max_delay)
    {
        set_delay(delay);
    }

    template <typename Allocator>
    AllpassSimple<Allocator>::AllpassSimple(Allocator& allocator, MdFloat max_delay,
        MdFloat delay, MdFloat gain) :
        Allpass<Allocator>(allocator, static_cast<std::uint32_t>(max_delay), gain)
    {
        set_delay(delay);
    }

    template <typename Allocator>
    void AllpassSimple<Allocator>::set_delay(MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), this->m_max_delay);

        this->m_delay = static_cast<std::uint32_t>(delay);
    }

    template <typename Allocator>
    MdFloat AllpassSimple<Allocator>::perform(MdFloat in) noexcept {
        auto phase = utility::wrap(this->m_write_index - this->m_delay, 0, this->m_upper_bound_1);

        auto sd = this->m_buffer[phase];
        auto s = in + this->m_gain * sd;

        this->write(s);
        this->increment();

        return sd - this->m_gain * s;
    }

}

#endif /* MD_AUDIO_ALLPASS_SIMPLE_HPP */
