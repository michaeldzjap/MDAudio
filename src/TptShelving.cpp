#include <cmath>
#include "TptShelving.hpp"

using md_audio::TptShelving;

double TptShelving::m2(double gain) noexcept {
    return std::pow(10., gain / 20.);
}
