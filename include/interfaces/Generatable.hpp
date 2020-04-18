#ifndef MD_AUDIO_GENERATABLE_HPP
#define MD_AUDIO_GENERATABLE_HPP

namespace md_audio {

    template <typename T>
    class Generatable {
    public:
        /**
         * Generate a single sample
         *
         * @return The generated sample
         */
        virtual T perform() noexcept = 0;
    };

}

#endif /* MD_AUDIO_GENERATABLE_HPP */
