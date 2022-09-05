#ifndef MD_AUDIO_TPT_SECOND_ORDER_HPP
#define MD_AUDIO_TPT_SECOND_ORDER_HPP

#include "TptFirstOrder.hpp"

namespace md_audio {

    class TptSecondOrder : public TptFirstOrder {
    protected:
        double m_s2 = 0.;
    };

}

#endif /* MD_AUDIO_TPT_SECOND_ORDER_HPP */
