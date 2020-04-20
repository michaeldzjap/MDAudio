#include "AllpassSimple.hpp"

using md_audio::AllpassSimple;
using md_audio::MdFloat;

AllpassSimple::AllpassSimple(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, MdFloat delay) :
    Allpass(allocator, max_delay)
{
    set_delay(delay);
}

AllpassSimple::AllpassSimple(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay,
    MdFloat delay, MdFloat gain) :
    Allpass(allocator, static_cast<std::uint32_t>(max_delay), gain)
{
    set_delay(delay);
}

void AllpassSimple::set_delay(MdFloat delay) noexcept {
    delay = utility::clip(delay, static_cast<MdFloat>(1), this->m_max_delay);

    this->m_delay = static_cast<std::uint32_t>(delay);
}

MdFloat AllpassSimple::perform(MdFloat in) noexcept {
    auto phase = utility::wrap(this->m_write_index - this->m_delay, 0, this->m_upper_bound_1);

    auto sd = this->m_buffer[phase];
    auto s = in + this->m_gain * sd;

    this->write(s);
    this->increment();

    return sd - this->m_gain * s;
}
