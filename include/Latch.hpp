#ifndef MD_AUDIO_LATCH_HPP
#define MD_AUDIO_LATCH_HPP

#include "interfaces/DuoProcessable.hpp"
#include "types.hpp"
#include "utility.hpp"

namespace md_audio {

    class Latch : public DuoProcessable<MdFloat, MdFloat> {
    public:
        Latch() = default;

        MdFloat perform(MdFloat, MdFloat) noexcept override final;

    private:
        MdFloat m_level = 0;
        MdFloat m_previous = 0;
    };

}

#endif /* MD_AUDIO_LATCH_HPP */
