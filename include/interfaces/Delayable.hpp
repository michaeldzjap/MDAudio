#ifndef MD_AUDIO_DELAYABLE_HPP
#define MD_AUDIO_DELAYABLE_HPP

#include "Processable.hpp"
#include "types.hpp"

namespace md_audio {

    class Delayable : public Processable<MdFloat, MdFloat> {
    public:
        /**
         * Set the delay time (in samples).
         *
         * @param  delay  The delay time in samples
         */
        virtual void set_delay(MdFloat delay) noexcept = 0;
    };

}

#endif /* MD_AUDIO_DELAYABLE_HPP */
