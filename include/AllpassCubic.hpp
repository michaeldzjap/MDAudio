#ifndef MD_AUDIO_ALLPASS_CUBIC_HPP
#define MD_AUDIO_ALLPASS_CUBIC_HPP

#include "Allpass.hpp"
#include "Processable.hpp"

namespace md_audio {

    template <typename Allocator>
    class AllpassCubic : public Processable<MdFloat, MdFloat>, public Allpass<Allocator> {
    public:
        explicit AllpassCubic(Allocator&, MdFloat, MdFloat);

        explicit AllpassCubic(Allocator&, MdFloat, MdFloat, MdFloat);

        inline void set_delay(MdFloat) noexcept override final;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        MdFloat m_frac;
    };

    template <typename Allocator>
    AllpassCubic<Allocator>::AllpassCubic(Allocator& allocator, MdFloat max_delay, MdFloat delay) :
        Allpass<Allocator>(allocator, max_delay)
    {
        set_delay(delay);
    }

    template <typename Allocator>
    AllpassCubic<Allocator>::AllpassCubic(Allocator& allocator, MdFloat max_delay,
        MdFloat delay, MdFloat gain) :
        Allpass<Allocator>(allocator, max_delay, gain)
    {
        set_delay(delay);
    }

    template <typename Allocator>
    void AllpassCubic<Allocator>::set_delay(MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), this->m_max_delay - 2);

        this->m_delay = static_cast<std::uint32_t>(delay);

        m_frac = delay - static_cast<MdFloat>(this->m_delay);
    }

    template <typename Allocator>
    MdFloat AllpassCubic<Allocator>::perform(MdFloat in) noexcept {
        auto phase_1 = utility::wrap(this->m_write_index - this->m_delay, 0, this->m_upper_bound_1);
        auto phase_2 = utility::wrap(phase_1 - 1, 0, this->m_upper_bound_1);
        auto phase_3 = utility::wrap(phase_1 - 2, 0, this->m_upper_bound_1);
        auto phase_0 = utility::wrap(phase_1 + 1, 0, this->m_upper_bound_1);

        auto d0 = this->m_buffer[phase_0];
        auto d1 = this->m_buffer[phase_1];
        auto d2 = this->m_buffer[phase_2];
        auto d3 = this->m_buffer[phase_3];

        auto sd = utility::cubic_interp(this->m_frac, d0, d1, d2, d3);
        auto s = in + this->m_gain * sd;

        this->write(s);
        this->increment();

        return sd - this->m_gain * s;
    }

}

#endif /* MD_AUDIO_ALLPASS_CUBIC_HPP */
