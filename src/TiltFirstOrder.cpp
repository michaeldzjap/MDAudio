#include <cmath>
#include "TiltFirstOrder.hpp"
#include "tpt.hpp"

using md_audio::TiltFirstOrder;

TiltFirstOrder::TiltFirstOrder() : LowpassFirstOrder() {
    set_gain(0.);
}

TiltFirstOrder::TiltFirstOrder(double frequency) :
    LowpassFirstOrder(frequency)
{
    set_gain(0.);
}

TiltFirstOrder::TiltFirstOrder(double frequency, double gain) :
    LowpassFirstOrder(frequency)
{
    set_gain(gain);
}

void TiltFirstOrder::set_gain(double gain) noexcept {
    m_m = std::sqrt(tpt::m2(gain));
    m_mi = 1. / m_m;
}

double TiltFirstOrder::process(double in) noexcept {
    auto y = LowpassFirstOrder::process(in);

    return m_mi * y + m_m * (in - y);
}
