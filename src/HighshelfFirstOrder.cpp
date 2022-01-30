#include "HighshelfFirstOrder.hpp"

using md_audio::HighshelfFirstOrder;

HighshelfFirstOrder::HighshelfFirstOrder() : LowpassFirstOrder() {
    set_gain(0.);
}

HighshelfFirstOrder::HighshelfFirstOrder(double frequency) :
    LowpassFirstOrder(frequency)
{
    set_gain(0.);
}

HighshelfFirstOrder::HighshelfFirstOrder(double frequency, double gain) :
    LowpassFirstOrder(frequency)
{
    set_gain(gain);
}

double HighshelfFirstOrder::process(double in) noexcept {
    auto y = LowpassFirstOrder::process(in);

    return y + m_m2 * (in - y);
}
