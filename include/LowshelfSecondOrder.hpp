#ifndef MD_AUDIO_LOWSHELF_SECOND_ORDER_HPP
#define MD_AUDIO_LOWSHELF_SECOND_ORDER_HPP

#include "TptSecondOrder.hpp"
#include "TptShelving.hpp"

namespace md_audio {

    class LowshelfSecondOrder : public TptSecondOrder, public TptShelving {
    public:
        explicit LowshelfSecondOrder();

        explicit LowshelfSecondOrder(double frequency);

        explicit LowshelfSecondOrder(double frequency, double r);

        explicit LowshelfSecondOrder(double frequency, double r, double gain);

        void set_gain(double gain) noexcept;

        double process(double in) noexcept;

    private:
        double m_m2i;
        double m_m4i;
    };

}

#endif /* MD_AUDIO_LOWSHELF_SECOND_ORDER_HPP */
