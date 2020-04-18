#ifndef MD_AUDIO_HIGHSHELF_HPP
#define MD_AUDIO_HIGHSHELF_HPP

#include "OnePole.hpp"
#include "Processable.hpp"
#include "Shelving.hpp"

namespace md_audio {

    class Highshelf : public Processable<MdFloat, MdFloat>, public Shelving, public OnePole {
    public:
        explicit Highshelf();

        explicit Highshelf(MdFloat);

        explicit Highshelf(MdFloat, MdFloat);

        MdFloat perform(MdFloat) noexcept override final;
    };

}

#endif /* MD_AUDIO_HIGHSHELF_HPP */
