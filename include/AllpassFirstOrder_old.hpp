#ifndef MD_AUDIO_ALLPASS_FIRST_ORDER_HPP
#define MD_AUDIO_ALLPASS_FIRST_ORDER_HPP

#include "OnePole.hpp"
#include "Processable.hpp"
#include "Zdf.hpp"

namespace md_audio {

    class AllpassFirstOrder : public Processable<MdFloat, MdFloat>, public Zdf, public OnePole {
    public:
        explicit AllpassFirstOrder();

        explicit AllpassFirstOrder(MdFloat);

        MdFloat perform(MdFloat) noexcept override final;
    };

}

#endif /* MD_AUDIO_ALLPASS_FIRST_ORDER_HPP */
