#ifndef MD_AUDIO_WHITE_NOISE_HPP
#define MD_AUDIO_WHITE_NOISE_HPP

#include <random>

namespace md_audio {

    class WhiteNoise {
    public:
        explicit WhiteNoise();

        double process() noexcept;

    private:
        std::random_device rd;
        std::default_random_engine urbg;
        std::uniform_real_distribution<double> dist;

        void initialise() noexcept;
    };

}

#endif /* MD_AUDIO_WHITE_NOISE_HPP */
