#include "AllpassLinear.hpp"

using md_audio::AllpassLinear;
using md_audio::MdFloat;

AllpassLinear::AllpassLinear(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, MdFloat delay) :
    Allpass(allocator, max_delay)
{
    set_delay(delay);
}

AllpassLinear::AllpassLinear(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay,
    MdFloat delay, MdFloat gain) :
    Allpass(allocator, max_delay, gain)
{
    set_delay(delay);
}

void AllpassLinear::set_delay(MdFloat delay) noexcept {
    delay = utility::clip(delay, static_cast<MdFloat>(1), this->m_max_delay - 1);

    this->m_delay = static_cast<std::uint32_t>(delay);

    m_frac = delay - static_cast<MdFloat>(this->m_delay);
}

MdFloat AllpassLinear::perform(MdFloat in) noexcept {
    auto phase_a = utility::wrap(this->m_write_index - this->m_delay, 0, this->m_upper_bound_1);
    auto phase_b = utility::wrap(phase_a - 1, 0, this->m_upper_bound_1);

    auto d1 = this->m_buffer[phase_a];
    auto d2 = this->m_buffer[phase_b];

    auto sd = utility::linear_interp(this->m_frac, d1, d2);
    auto s = in + this->m_gain * sd;

    this->write(s);
    this->increment();

    return sd - this->m_gain * s;
}
