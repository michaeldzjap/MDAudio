#include "AllpassCubic.hpp"

using md_audio::AllpassCubic;
using md_audio::MdFloat;

AllpassCubic::AllpassCubic(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, MdFloat delay) :
    Allpass(allocator, max_delay)
{
    set_delay(delay);
}

AllpassCubic::AllpassCubic(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay,
    MdFloat delay, MdFloat gain) :
    Allpass(allocator, max_delay, gain)
{
    set_delay(delay);
}

void AllpassCubic::set_delay(MdFloat delay) noexcept {
    delay = utility::clip(delay, static_cast<MdFloat>(1), this->m_max_delay - 2);

    this->m_delay = static_cast<std::uint32_t>(delay);

    m_frac = delay - static_cast<MdFloat>(this->m_delay);
}

MdFloat AllpassCubic::perform(MdFloat in) noexcept {
    auto phase_1 = utility::wrap(this->m_write_index - this->m_delay, 0, this->m_upper_bound_1);
    auto phase_2 = utility::wrap(phase_1 - 1, 0, this->m_upper_bound_1);
    auto phase_3 = utility::wrap(phase_1 - 2, 0, this->m_upper_bound_1);
    auto phase_0 = utility::wrap(phase_1 + 1, 0, this->m_upper_bound_1);

    auto d0 = this->m_buffer[phase_0];
    auto d1 = this->m_buffer[phase_1];
    auto d2 = this->m_buffer[phase_2];
    auto d3 = this->m_buffer[phase_3];

    auto sd = utility::cubic_interp(this->m_frac, d0, d1, d2, d3);
    auto s = in + this->m_gain * sd;

    this->write(s);
    this->increment();

    return sd - this->m_gain * s;
}
