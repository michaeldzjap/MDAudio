#ifndef MD_AUDIO_LOWSHELF_FIRST_ORDER_HPP
#define MD_AUDIO_LOWSHELF_FIRST_ORDER_HPP

#include "TptShelvingFirstOrder.hpp"

namespace md_audio {

    class LowshelfFirstOrder : public TptShelvingFirstOrder {
    public:
        explicit LowshelfFirstOrder();

        explicit LowshelfFirstOrder(double frequency);

        explicit LowshelfFirstOrder(double frequency, double gain);

        double process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_LOWSHELF_FIRST_ORDER_HPP */
