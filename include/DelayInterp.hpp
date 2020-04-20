#ifndef MD_AUDIO_DELAY_INTERP_HPP
#define MD_AUDIO_DELAY_INTERP_HPP

#include "Delay.hpp"
#include "types.hpp"
#include "utility.hpp"
#include <array>

namespace md_audio {

    class DelayInterp : public Delay {
    public:
        explicit DelayInterp(memory::Allocatable<MdFloat*>&, MdFloat);

        void set_delay(MdFloat) noexcept override final;

        virtual ~DelayInterp() = 0;

    protected:
        MdFloat m_frac;
    };

}

#endif /* MD_AUDIO_DELAY_INTERP_HPP */
