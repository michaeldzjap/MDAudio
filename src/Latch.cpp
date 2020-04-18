#include "Latch.hpp"

using md_audio::Latch;
using md_audio::MdFloat;

MdFloat Latch::perform(MdFloat in1, MdFloat in2) noexcept {
    if (in2 - m_previous <= static_cast<MdFloat>(0))
        m_level = in1;

    m_previous = in2;

    return m_level;
}
