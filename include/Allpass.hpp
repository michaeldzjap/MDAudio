#ifndef MD_AUDIO_ALLPASS_HP
#define MD_AUDIO_ALLPASS_HP

#include "Writer.hpp"

namespace md_audio {

    class Allpass : public Writer {
    public:
        explicit Allpass(memory::Allocatable<MdFloat*>&, MdFloat);

        explicit Allpass(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat);

        virtual void set_delay(MdFloat) noexcept = 0;

        virtual inline void set_gain(MdFloat gain) noexcept {
            m_gain = utility::clip(gain, static_cast<MdFloat>(0), static_cast<MdFloat>(1));
        }

    protected:
        std::uint32_t m_delay;
        MdFloat m_max_delay;
        MdFloat m_gain = 0.;
    };

}

#endif /* MD_AUDIO_ALLPASS_HP */
