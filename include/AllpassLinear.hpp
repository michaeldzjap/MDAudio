#ifndef MD_AUDIO_ALLPASS_LINEAR_HPP
#define MD_AUDIO_ALLPASS_LINEAR_HPP

#include "Allpass.hpp"
#include "Processable.hpp"

namespace md_audio {

    class AllpassLinear : public Processable<MdFloat, MdFloat>, public Allpass {
    public:
        explicit AllpassLinear(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat);

        explicit AllpassLinear(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat, MdFloat);

        inline void set_delay(MdFloat) noexcept override final;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        MdFloat m_frac;
    };

}

#endif /* MD_AUDIO_ALLPASS_LINEAR_HPP */
