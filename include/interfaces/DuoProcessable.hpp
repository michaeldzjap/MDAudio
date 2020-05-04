#ifndef MD_AUDIO_DUO_PROCESSABLE_HPP
#define MD_AUDIO_DUO_PROCESSABLE_HPP

namespace md_audio {

    template <typename U, typename V>
    class DuoProcessable {
    public:
        /**
         * Process a single sample.
         *
         * @param  in1  The first input sample
         * @param  in2  The second input sample
         * @return      The processed sample
         */
        virtual U perform(V in1, V in2) noexcept = 0;
    };

}

#endif /* MD_AUDIO_DUO_PROCESSABLE_HPP */
