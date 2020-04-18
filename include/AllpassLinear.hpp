#ifndef MD_AUDIO_ALLPASS_LINEAR_HPP
#define MD_AUDIO_ALLPASS_LINEAR_HPP

#include "Allpass.hpp"
#include "Processable.hpp"

namespace md_audio {

    template <typename Allocator>
    class AllpassLinear : public Processable<MdFloat, MdFloat>, public Allpass<Allocator> {
    public:
        explicit AllpassLinear(Allocator&, MdFloat, MdFloat);

        explicit AllpassLinear(Allocator&, MdFloat, MdFloat, MdFloat);

        inline void set_delay(MdFloat) noexcept override final;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        MdFloat m_frac;
    };

    template <typename Allocator>
    AllpassLinear<Allocator>::AllpassLinear(Allocator& allocator, MdFloat max_delay, MdFloat delay) :
        Allpass<Allocator>(allocator, max_delay)
    {
        set_delay(delay);
    }

    template <typename Allocator>
    AllpassLinear<Allocator>::AllpassLinear(Allocator& allocator, MdFloat max_delay,
        MdFloat delay, MdFloat gain) :
        Allpass<Allocator>(allocator, max_delay, gain)
    {
        set_delay(delay);
    }

    template <typename Allocator>
    void AllpassLinear<Allocator>::set_delay(MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), this->m_max_delay - 1);

        this->m_delay = static_cast<std::uint32_t>(delay);

        m_frac = delay - static_cast<MdFloat>(this->m_delay);
    }

    template <typename Allocator>
    MdFloat AllpassLinear<Allocator>::perform(MdFloat in) noexcept {
        auto phase_a = utility::wrap(this->m_write_index - this->m_delay, 0, this->m_upper_bound_1);
        auto phase_b = utility::wrap(phase_a - 1, 0, this->m_upper_bound_1);

        auto d1 = this->m_buffer[phase_a];
        auto d2 = this->m_buffer[phase_b];

        auto sd = utility::linear_interp(this->m_frac, d1, d2);
        auto s = in + this->m_gain * sd;

        this->write(s);
        this->increment();

        return sd - this->m_gain * s;
    }

}

#endif /* MD_AUDIO_ALLPASS_LINEAR_HPP */
