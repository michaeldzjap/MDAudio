#ifndef MD_AUDIO_SHELVING_HPP
#define MD_AUDIO_SHELVING_HPP

#include "Zdf.hpp"
#include "types.hpp"
#include <cmath>

namespace md_audio {

    class Shelving : public Zdf {
    public:
        explicit Shelving();

        explicit Shelving(MdFloat);

        inline void set_frequency(MdFloat frequency) noexcept override final {
            Zdf::set_frequency(frequency);

            m_h = m_g / (1. + m_g);
        }

        inline virtual void set_gain(MdFloat gain) noexcept {
            m_m2 = compute_m2(static_cast<double>(gain));
        }

        virtual ~Shelving() = 0;

    protected:
        double m_m2;
        double m_h;

    private:
        inline static double compute_m2(double gain) noexcept {
            return std::pow(10., gain / 20.);
        }
    };

}

#endif /* MD_AUDIO_SHELVING_HPP */
