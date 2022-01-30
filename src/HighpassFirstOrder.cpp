#include "HighpassFirstOrder.hpp"

using md_audio::HighpassFirstOrder;

HighpassFirstOrder::HighpassFirstOrder() : LowpassFirstOrder() {}

HighpassFirstOrder::HighpassFirstOrder(double frequency) :
    LowpassFirstOrder(frequency)
{}

double HighpassFirstOrder::process(double in) noexcept {
    return in - LowpassFirstOrder::process(in);
}
