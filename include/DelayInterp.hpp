#ifndef MD_AUDIO_DELAY_INTERP_HPP
#define MD_AUDIO_DELAY_INTERP_HPP

#include "Delay.hpp"
#include "types.hpp"
#include "utility.hpp"
#include <array>

namespace md_audio {

    template <typename Allocator>
    class DelayInterp : public Delay<Allocator> {
    public:
        explicit DelayInterp(Allocator&, MdFloat);

        void set_delay(MdFloat) noexcept override final;

        virtual ~DelayInterp() = 0;

    protected:
        MdFloat m_frac;
    };

    template <typename Allocator>
    DelayInterp<Allocator>::DelayInterp(Allocator& allocator, MdFloat max_delay) :
        Delay<Allocator>(allocator, max_delay)
    {}

    template <typename Allocator>
    void DelayInterp<Allocator>::set_delay(MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), this->get_max_delay());

        this->m_delay = static_cast<std::uint32_t>(delay);

        m_frac = delay - static_cast<MdFloat>(this->m_delay);
    }

    template <typename Allocator>
    DelayInterp<Allocator>::~DelayInterp() {}

}

#endif /* MD_AUDIO_DELAY_INTERP_HPP */
