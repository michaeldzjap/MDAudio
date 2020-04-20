#ifndef MD_AUDIO_DELAY_SIMPLE_HPP
#define MD_AUDIO_DELAY_SIMPLE_HPP

#include "Delay.hpp"

namespace md_audio {

    class DelaySimple : public Delay {
    public:
        explicit DelaySimple(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat);

        inline void set_delay(MdFloat) noexcept override final;

        inline MdFloat get_max_delay() noexcept override final;

        MdFloat read() noexcept override final;
    };

}

#endif /* MD_AUDIO_DELAY_SIMPLE_HPP */
