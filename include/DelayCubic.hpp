#ifndef MD_AUDIO_DELAY_CUBIC_HPP
#define MD_AUDIO_DELAY_CUBIC_HPP

#include "DelayInterp.hpp"

namespace md_audio {

    class DelayCubic : public DelayInterp {
    public:
        explicit DelayCubic(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat);

        inline MdFloat get_max_delay() noexcept override final;

        MdFloat read() noexcept override final;
    };

}

#endif /* MD_AUDIO_DELAY_CUBIC_HPP */
