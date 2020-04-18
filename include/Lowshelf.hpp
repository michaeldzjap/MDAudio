#ifndef MD_AUDIO_LOWSHELF_HPP
#define MD_AUDIO_LOWSHELF_HPP

#include "OnePole.hpp"
#include "Processable.hpp"
#include "Shelving.hpp"

namespace md_audio {

    class Lowshelf : public Processable<MdFloat, MdFloat>, public Shelving, public OnePole {
    public:
        explicit Lowshelf();

        explicit Lowshelf(MdFloat);

        explicit Lowshelf(MdFloat, MdFloat);

        inline virtual void set_gain(MdFloat gain) noexcept override final {
            Shelving::set_gain(-gain);

            m_m2i = 1. / m_m2;
        }

        MdFloat perform(MdFloat) noexcept override final;

    private:
        double m_m2i;
    };

}

#endif /* MD_AUDIO_LOWSHELF_HPP */
