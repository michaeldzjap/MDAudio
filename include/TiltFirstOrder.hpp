#ifndef MD_AUTIO_TILT_FIRST_ORDER_HPP
#define MD_AUTIO_TILT_FIRST_ORDER_HPP

#include "TptFilter.hpp"
#include "TptShelving.hpp"
#include "interfaces/Processable.hpp"

namespace md_audio {

    class TiltFirstOrder :
        public TptFilter,
        public TptShelving,
        public Processable<MdFloat, MdFloat>
    {
    public:
        explicit TiltFirstOrder();

        explicit TiltFirstOrder(MdFloat);

        explicit TiltFirstOrder(MdFloat, MdFloat);

        inline void set_frequency(MdFloat) noexcept;

        inline void set_gain(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        double m_s = 0.;
        double m_g;
        double m_m;
        double m_mi;
    };

    void TiltFirstOrder::set_frequency(MdFloat frequency) noexcept {
        m_g = g(static_cast<double>(frequency));
    }

    void TiltFirstOrder::set_gain(MdFloat gain) noexcept {
        m_m = std::sqrt(m2(gain));
        m_mi = 1. / m_m;
    }

}

#endif /* MD_AUTIO_TILT_FIRST_ORDER_HPP */
