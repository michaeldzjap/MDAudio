#ifndef MD_AUDIO_BLOCK_PROCESSABLE_HPP
#define MD_AUDIO_BLOCK_PROCESSABLE_HPP

#include <cstddef>

namespace md_audio {

    template <typename U, typename V>
    class BlockProcessable {
    public:
        /**
         * Process a block of samples.
         *
         * @param  in   The input sample buffer
         * @param  out  The output sample buffer
         * @param  n    The number of samples in the input and output buffers
         * @return      The processed sample buffer
         */
        virtual U* perform(V* in, U* out, std::size_t n) noexcept = 0;
    };

}

#endif /* MD_AUDIO_BLOCK_PROCESSABLE_HPP */
