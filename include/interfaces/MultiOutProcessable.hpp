#ifndef MD_AUDIO_MULTI_OUT_PROCESSABLE_HPP
#define MD_AUDIO_MULTI_OUT_PROCESSABLE_HPP

#include <cstddef>

namespace md_audio {

    template <typename U, typename V>
    class MultiOutProcessable {
    public:
        /**
         * Process a single sample for multiple outputs.
         *
         * @param  in   The input sample
         * @param  out  The output sample buffer
         * @param  n    The number of samples in the output buffer
         * @return      The processed sample buffer
         */
        virtual U* perform(V in, U* out, std::size_t n) noexcept = 0;
    };

}

#endif /* MD_AUDIO_MULTI_OUT_PROCESSABLE_HPP */
