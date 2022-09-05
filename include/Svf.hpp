#ifndef MD_AUDIO_SVF_HPP
#define MD_AUDIO_SVF_HPP

#include <array>
#include "TptSecondOrder.hpp"
#include "Unit.hpp"

namespace md_audio {

    enum Output { LP, HP, BP };

    class Svf : public Unit, public TptSecondOrder {
    public:
        explicit Svf();

        explicit Svf(double frequency);

        explicit Svf(double frequency, double r);

        void set_frequency(double frequency) noexcept;

        void set_r(double r) noexcept;

        double process(double in, Output output) noexcept;

        std::array<double, 3> process(double in) noexcept;

    protected:
        double m_g;
        double m_r2;
    };

}

#endif /* MD_AUDIO_SVF_HPP */
