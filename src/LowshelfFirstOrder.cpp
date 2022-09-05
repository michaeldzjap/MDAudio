#include "LowshelfFirstOrder.hpp"

using md_audio::LowshelfFirstOrder;

LowshelfFirstOrder::LowshelfFirstOrder() : LowpassFirstOrder() {
    set_gain(0.);
}

LowshelfFirstOrder::LowshelfFirstOrder(double frequency) :
    LowpassFirstOrder(frequency)
{
    set_gain(0.);
}

LowshelfFirstOrder::LowshelfFirstOrder(double frequency, double gain) :
    LowpassFirstOrder(frequency)
{
    set_gain(gain);
}

double LowshelfFirstOrder::process(double in) noexcept {
    auto y = LowpassFirstOrder::process(in);

    return m_m2 * y + in - y;
}
