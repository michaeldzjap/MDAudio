#ifndef MD_AUDIO_BANDSHELF_HPP
#define MD_AUDIO_BANDSHELF_HPP

#include "TptSecondOrder.hpp"

namespace md_audio {

    class Bandshelf : public TptSecondOrder {
    public:
        explicit Bandshelf();

        explicit Bandshelf(double frequency);

        explicit Bandshelf(double frequency, double r);

        explicit Bandshelf(double frequency, double r, double gain);

        void set_gain(double gain) noexcept;

        double process(double in) noexcept;

    private:
        double m_m2;
    };

}

#endif /* MD_AUDIO_BANDSHELF_HPP */
