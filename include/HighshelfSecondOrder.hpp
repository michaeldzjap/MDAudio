#ifndef MD_AUDIO_HIGHSHELF_SECOND_ORDER_HPP
#define MD_AUDIO_HIGHSHELF_SECOND_ORDER_HPP

#include "ShelvingSecondOrder.hpp"
#include "Svf.hpp"

namespace md_audio {

    class HighshelfSecondOrder : public Svf, public ShelvingSecondOrder {
    public:
        explicit HighshelfSecondOrder();

        explicit HighshelfSecondOrder(double frequency);

        explicit HighshelfSecondOrder(double frequency, double r);

        explicit HighshelfSecondOrder(double frequency, double r, double gain);

        double process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_HIGHSHELF_SECOND_ORDER_HPP */
