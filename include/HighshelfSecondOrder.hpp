#ifndef MD_AUDIO_HIGHSHELF_SECOND_ORDER_HPP
#define MD_AUDIO_HIGHSHELF_SECOND_ORDER_HPP

#include "TptShelvingSecondOrder.hpp"

namespace md_audio {

    class HighshelfSecondOrder : public TptShelvingSecondOrder {
    public:
        explicit HighshelfSecondOrder();

        explicit HighshelfSecondOrder(double frequency);

        explicit HighshelfSecondOrder(double frequency, double r);

        explicit HighshelfSecondOrder(double frequency, double r, double gain);

        double process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_HIGHSHELF_SECOND_ORDER_HPP */
