#ifndef MD_AUDIO_ALLPASS_CUBIC_HPP
#define MD_AUDIO_ALLPASS_CUBIC_HPP

#include "Allpass.hpp"
#include "Processable.hpp"

namespace md_audio {

    class AllpassCubic : public Processable<MdFloat, MdFloat>, public Allpass {
    public:
        explicit AllpassCubic(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat);

        explicit AllpassCubic(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat, MdFloat);

        inline void set_delay(MdFloat) noexcept override final;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        MdFloat m_frac;
    };

}

#endif /* MD_AUDIO_ALLPASS_CUBIC_HPP */
