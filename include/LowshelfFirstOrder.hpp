#ifndef MD_AUDIO_LOWSHELF_FIRST_ORDER_HPP
#define MD_AUDIO_LOWSHELF_FIRST_ORDER_HPP

#include "LowpassFirstOrder.hpp"
#include "ShelvingFirstOrder.hpp"

namespace md_audio {

    class LowshelfFirstOrder : public LowpassFirstOrder, public ShelvingFirstOrder {
    public:
        explicit LowshelfFirstOrder();

        explicit LowshelfFirstOrder(double frequency);

        explicit LowshelfFirstOrder(double frequency, double gain);

        double process(double in) noexcept;
    };

}

#endif /* MD_AUDIO_LOWSHELF_FIRST_ORDER_HPP */
