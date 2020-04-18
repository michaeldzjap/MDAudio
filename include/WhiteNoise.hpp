#ifndef MD_AUDIO_WHITE_NOISE_HPP
#define MD_AUDIO_WHITE_NOISE_HPP

#include "Generatable.hpp"
#include "Taus88.hpp"
#include "types.hpp"

namespace md_audio {

    class WhiteNoise : public Generatable<MdFloat> {
    public:
        WhiteNoise() = default;

        MdFloat perform() noexcept override final;

    private:
        Taus88 m_generator;
    };

}

#endif /* MD_AUDIO_WHITE_NOISE_HPP */
