#include "WhiteNoise.hpp"

using md_audio::MdFloat;
using md_audio::WhiteNoise;

MdFloat WhiteNoise::perform() noexcept {
    return static_cast<MdFloat>(m_generator.generate());
}
