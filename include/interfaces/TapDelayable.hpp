#ifndef MD_AUDIO_TAP_DELAYABLE_HPP
#define MD_AUDIO_TAP_DELAYABLE_HPP

#include "MultiOutProcessable.hpp"
#include "types.hpp"

namespace md_audio {

    class TapDelayable : MultiOutProcessable<MdFloat, MdFloat> {
    public:
        /**
         * Initialise the delay line.
         */
        virtual void initialise() = 0;

        /**
         * Set the tap delay times (in samples).
         *
         * @param  delay  A pointer to the tap delay times in samples
         */
        virtual void set_delay(const MdFloat* delay) noexcept = 0;

        /**
         * Set a specific tap delay time (in samples).
         *
         * @param  index  The tap index
         * @param  delay  The delay time in samples
         */
        virtual void set_delay(std::size_t index, MdFloat delay) noexcept = 0;

        /**
         * Get the maximum allowed delay time (in samples).
         *
         * @return The maximum delay time in samples
         */
        virtual constexpr MdFloat get_max_delay() noexcept = 0;

        /**
         * Write an input sample to the delay line.
         *
         * @param  in  The input sample
         */
        virtual void write(MdFloat in) noexcept = 0;

        /**
         * Read an output sample from a tap of the delay line.
         *
         * @param  index  The tap index
         * @return        The output sample
         */
        virtual MdFloat read(std::size_t index) noexcept = 0;
    };

}

#endif /* MD_AUDIO_TAP_DELAYABLE_HPP */
