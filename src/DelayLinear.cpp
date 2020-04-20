#include "DelayLinear.hpp"

using md_audio::DelayLinear;
using md_audio::MdFloat;

DelayLinear::DelayLinear(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, MdFloat delay) :
    DelayInterp(allocator, max_delay)
{
    this->set_delay(delay);
}

MdFloat DelayLinear::get_max_delay() noexcept {
    return this->m_max_delay - 1;
}

MdFloat DelayLinear::read() noexcept {
    // Get the correct read positions into the buffer
    auto phase_a = utility::wrap(this->m_write_index - this->m_delay, 0, this->m_upper_bound_1);
    auto phase_b = utility::wrap(phase_a - 1, 0, this->m_upper_bound_1);

    auto d1 = this->m_buffer[phase_a];
    auto d2 = this->m_buffer[phase_b];

    return utility::linear_interp(this->m_frac, d1, d2);
}
