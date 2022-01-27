#ifndef MD_AUDIO_LOWSHELF_SECOND_ORDER_HPP
#define MD_AUDIO_LOWSHELF_SECOND_ORDER_HPP

#include "TptShelvingSecondOrder.hpp"

namespace md_audio {

    class LowshelfSecondOrder : public TptShelvingSecondOrder {
    public:
        explicit LowshelfSecondOrder();

        explicit LowshelfSecondOrder(double frequency);

        explicit LowshelfSecondOrder(double frequency, double r);

        explicit LowshelfSecondOrder(double frequency, double r, double gain);

        double process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_LOWSHELF_SECOND_ORDER_HPP */
