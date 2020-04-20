#ifndef MD_AUDIO_ALLPASS_SIMPLE_HPP
#define MD_AUDIO_ALLPASS_SIMPLE_HPP

#include "Allpass.hpp"
#include "Processable.hpp"

namespace md_audio {

    class AllpassSimple : public Processable<MdFloat, MdFloat>, public Allpass {
    public:
        explicit AllpassSimple(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat);

        explicit AllpassSimple(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat, MdFloat);

        inline void set_delay(MdFloat) noexcept override final;

        MdFloat perform(MdFloat) noexcept override final;
    };

}

#endif /* MD_AUDIO_ALLPASS_SIMPLE_HPP */
