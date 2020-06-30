#ifndef MD_AUDIO_TPT_SECOND_ORDER_HPP
#define MD_AUDIO_TPT_SECOND_ORDER_HPP

#include "utility.hpp"

namespace md_audio {

    class TptSecondOrder {
    public:
        virtual ~TptSecondOrder() = 0;

    protected:
        inline auto r2(double) noexcept;

        inline auto d(double, double) noexcept;
    };

    auto TptSecondOrder::r2(double r) noexcept {
        r = utility::max(r, 0.);

        return r + r;
    }

    auto TptSecondOrder::d(double r2, double g) noexcept {
        return 1. / (1. + r2 * g + g * g);
    }

}

#endif /* MD_AUDIO_TPT_SECOND_ORDER_HPP */
