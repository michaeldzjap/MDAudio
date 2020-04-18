#include "Shelving.hpp"

using md_audio::MdFloat;
using md_audio::Shelving;

Shelving::Shelving() {
    set_gain(static_cast<MdFloat>(0));
}

Shelving::Shelving(MdFloat gain) {
    set_gain(gain);
}

Shelving::~Shelving() {}
