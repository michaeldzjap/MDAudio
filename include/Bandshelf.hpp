#ifndef MD_AUDIO_BANDSHELF_HPP
#define MD_AUDIO_BANDSHELF_HPP

#include "Svf.hpp"

namespace md_audio {

    class Bandshelf : public Svf {
    public:
        explicit Bandshelf();

        explicit Bandshelf(double frequency);

        explicit Bandshelf(double frequency, double r);

        explicit Bandshelf(double frequency, double r, double gain);

        void set_gain(double gain) noexcept;

        double process(double in) noexcept;

    private:
        double m_m2i;
    };

}

#endif /* MD_AUDIO_BANDSHELF_HPP */
