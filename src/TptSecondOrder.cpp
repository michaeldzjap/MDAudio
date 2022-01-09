#include "TptSecondOrder.hpp"
#include "utility.hpp"

using md_audio::TptSecondOrder;

void TptSecondOrder::set_frequency(double frequency) noexcept {
    m_g = g(frequency);
}

void TptSecondOrder::set_r(double r) noexcept {
    m_r2 = r2(r);
}

double TptSecondOrder::r2(double r) noexcept {
    r = utility::max(r, 0.);

    return r + r;
}

double TptSecondOrder::d(double r2, double g) noexcept {
    return 1. / (1. + r2 * g + g * g);
}
