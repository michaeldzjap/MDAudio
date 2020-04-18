#ifndef MD_AUDIO_ALLPASS_HP
#define MD_AUDIO_ALLPASS_HP

#include "Writer.hpp"

namespace md_audio {

    template <typename Allocator>
    class Allpass : public Writer<Allocator> {
    public:
        explicit Allpass(Allocator&, MdFloat);

        explicit Allpass(Allocator&, MdFloat, MdFloat);

        virtual void set_delay(MdFloat) noexcept = 0;

        virtual inline void set_gain(MdFloat gain) noexcept {
            m_gain = utility::clip(gain, static_cast<MdFloat>(0), static_cast<MdFloat>(1));
        }

    protected:
        std::uint32_t m_delay;
        MdFloat m_max_delay;
        MdFloat m_gain = 0.;
    };

    template <typename Allocator>
    Allpass<Allocator>::Allpass(Allocator& allocator, MdFloat max_delay) :
        Writer<Allocator>(allocator, static_cast<std::uint32_t>(max_delay)),
        m_max_delay(max_delay)
    {}

    template <typename Allocator>
    Allpass<Allocator>::Allpass(Allocator& allocator, MdFloat max_delay, MdFloat gain) :
        Writer<Allocator>(allocator, static_cast<std::uint32_t>(max_delay)),
        m_max_delay(max_delay)
    {
        set_gain(gain);
    }

}

#endif /* MD_AUDIO_ALLPASS_HP */
