#ifndef MD_AUDIO_DELAY_LINEAR_HPP
#define MD_AUDIO_DELAY_LINEAR_HPP

#include "DelayInterp.hpp"

namespace md_audio {

    class DelayLinear : public DelayInterp {
    public:
        explicit DelayLinear(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat);

        inline MdFloat get_max_delay() noexcept override final;

        MdFloat read() noexcept override final;
    };

}

#endif /* MD_AUDIO_DELAY_LINEAR_HPP */
