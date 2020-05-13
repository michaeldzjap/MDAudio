#ifndef MD_AUDIO_PROCESSABLE_HPP
#define MD_AUDIO_PROCESSABLE_HPP

namespace md_audio {

    template <typename U, typename V>
    class Processable {
    public:
        /**
         * Process a single sample.
         *
         * @param  in  The input sample
         * @return     The processed sample
         */
        virtual U perform(V in) noexcept = 0;
    };

}

#endif /* MD_AUDIO_PROCESSABLE_HPP */
