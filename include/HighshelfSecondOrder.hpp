#ifndef MD_AUDIO_HIGHSHELF_SECOND_ORDER_HPP
#define MD_AUDIO_HIGHSHELF_SECOND_ORDER_HPP

#include "TptSecondOrder.hpp"
#include "TptShelving.hpp"

namespace md_audio {

    class HighshelfSecondOrder : public TptSecondOrder, public TptShelving {
    public:
        explicit HighshelfSecondOrder();

        explicit HighshelfSecondOrder(double frequency);

        explicit HighshelfSecondOrder(double frequency, double r);

        explicit HighshelfSecondOrder(double frequency, double r, double gain);

        void set_gain(double gain) noexcept;

        double process(double in) noexcept;

    private:
        double m_m2;
        double m_m4;
    };

}

#endif /* MD_AUDIO_HIGHSHELF_SECOND_ORDER_HPP */
