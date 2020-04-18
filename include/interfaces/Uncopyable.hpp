#ifndef MD_AUDIO_UNCOPYABLE_HPP
#define MD_AUDIO_UNCOPYABLE_HPP

namespace md_audio::util {

    class Uncopyable {
    public:
        constexpr Uncopyable() = default;

        Uncopyable(const Uncopyable&) = delete;

        Uncopyable& operator=(const Uncopyable&) = delete;

        /**
         * So we have the ability to delete the class in a polymorphic context.
         */
        ~Uncopyable() = default;
    };

}

#endif /* MD_AUDIO_UNCOPYABLE_HPP */
