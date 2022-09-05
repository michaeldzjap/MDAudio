#include <chrono>
#include "WhiteNoise.hpp"

using md_audio::WhiteNoise;

WhiteNoise::WhiteNoise() :
    urbg(rd()),
    dist(-1., std::nextafter(1., 2.))
{
    initialise();
}

void WhiteNoise::initialise() noexcept {
    auto now = std::chrono::high_resolution_clock::now();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());

    urbg.seed(seconds.count());
}

double WhiteNoise::process() noexcept {
    return dist(urbg);
}
