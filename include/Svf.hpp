#ifndef MD_AUDIO_SVF_HPP
#define MD_AUDIO_SVF_HPP

#include "TptFilter.hpp"
#include "TptSecondOrder.hpp"
#include "interfaces/Processable.hpp"

namespace md_audio {

    class Svf :
        public TptFilter,
        public TptSecondOrder,
        public Processable<std::array<MdFloat, 3>, MdFloat>
    {
    public:
        explicit Svf();

        explicit Svf(MdFloat);

        explicit Svf(MdFloat, MdFloat);

        inline void set_frequency(MdFloat) noexcept;

        inline void set_r(MdFloat) noexcept;

        std::array<MdFloat, 3> perform(MdFloat) noexcept override final;

    private:
        double m_s1 = 0.;
        double m_s2 = 0.;
        double m_g;
        double m_r2;
    };

    void Svf::set_frequency(MdFloat frequency) noexcept {
        m_g = g(static_cast<double>(frequency));
    }

    void Svf::set_r(MdFloat r) noexcept {
        m_r2 = r2(static_cast<double>(r));
    }

}

#endif /* MD_AUDIO_SVF_HPP */
