#include "DelayCubic.hpp"

using md_audio::DelayCubic;
using md_audio::MdFloat;

DelayCubic::DelayCubic(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, MdFloat delay) :
    DelayInterp(allocator, max_delay)
{
    this->set_delay(delay);
}

MdFloat DelayCubic::get_max_delay() noexcept {
    return this->m_max_delay - 2;
}

MdFloat DelayCubic::read() noexcept {
    // Get the correct read positions into the buffer
    auto phase_1 = utility::wrap(this->m_write_index - this->m_delay, 0, this->m_upper_bound_1);
    auto phase_2 = utility::wrap(phase_1 - 1, 0, this->m_upper_bound_1);
    auto phase_3 = utility::wrap(phase_1 - 2, 0, this->m_upper_bound_1);
    auto phase_0 = utility::wrap(phase_1 + 1, 0, this->m_upper_bound_1);

    auto d0 = this->m_buffer[phase_0];
    auto d1 = this->m_buffer[phase_1];
    auto d2 = this->m_buffer[phase_2];
    auto d3 = this->m_buffer[phase_3];

    return utility::cubic_interp(this->m_frac, d0, d1, d2, d3);
}
