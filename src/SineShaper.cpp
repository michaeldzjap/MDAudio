#include "SineShaper.hpp"
#include "tables.hpp"

using md_audio::MdFloat;
using md_audio::SineShaper;

SineShaper::SineShaper(MdFloat limit) {
    set_limit(limit);
}

MdFloat SineShaper::perform(MdFloat in) noexcept {
    auto offset = in * m_phase_rate;

    while (offset < 0.) offset += static_cast<double>(table_size);
    while (offset >= table_size) offset -= static_cast<double>(table_size);

    return m_limit * utility::lookup(sine_table, offset);
}
