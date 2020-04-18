#ifndef MD_AUDIO_BLOCK_PROCESSABLE_HPP
#define MD_AUDIO_BLOCK_PROCESSABLE_HPP

#include <cstdint>

namespace md_audio {

    template <typename U, typename V>
    class BlockProcessable {
    public:
        /**
         * Process a block of samples.
         *
         * @param  in  The input sample buffer
         * @param  out The output sample buffer
         * @param  n   The number of samples in the input and output buffers
         * @return     The processed sample buffer
         */
        virtual void perform(V* in, U* out, std::uint16_t n) noexcept = 0;
    };

}

#endif /* MD_AUDIO_BLOCK_PROCESSABLE_HPP */
