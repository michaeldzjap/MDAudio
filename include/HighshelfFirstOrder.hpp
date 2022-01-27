#ifndef MD_AUDIO_HIGHSHELF_FIRST_ORDER_HPP
#define MD_AUDIO_HIGHSHELF_FIRST_ORDER_HPP

#include "TptShelvingFirstOrder.hpp"

namespace md_audio {

    class HighshelfFirstOrder : public TptShelvingFirstOrder {
    public:
        explicit HighshelfFirstOrder();

        explicit HighshelfFirstOrder(double frequency);

        explicit HighshelfFirstOrder(double frequency, double gain);

        double process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_HIGHSHELF_FIRST_ORDER_HPP */
