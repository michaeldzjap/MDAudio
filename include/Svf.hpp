#ifndef MD_AUDIO_SVF_HPP
#define MD_AUDIO_SVF_HPP

#include <array>
#include "TptSecondOrder.hpp"

namespace md_audio {

    class Svf : public TptSecondOrder {
    public:
        explicit Svf();

        explicit Svf(double frequency);

        explicit Svf(double frequency, double r);

        std::array<double, 3> process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_SVF_HPP */
