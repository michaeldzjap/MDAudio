#include "AllpassFirstOrder.hpp"

using md_audio::AllpassFirstOrder;

AllpassFirstOrder::AllpassFirstOrder() : LowpassFirstOrder() {}

AllpassFirstOrder::AllpassFirstOrder(double frequency) :
    LowpassFirstOrder(frequency)
{}

double AllpassFirstOrder::process(double in) noexcept {
    auto y = LowpassFirstOrder::process(in);

    return y - (in - y);
}
