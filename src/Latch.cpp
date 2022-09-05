#include "Latch.hpp"

using md_audio::Latch;

double Latch::process(double in1, double in2) noexcept {
    if (in2 - m_previous <= 0.)
        m_level = in1;

    m_previous = in2;

    return m_level;
}
