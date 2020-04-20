#include "DelaySimple.hpp"

using md_audio::DelaySimple;
using md_audio::MdFloat;

DelaySimple::DelaySimple(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, MdFloat delay) :
    Delay(allocator, max_delay)
{
    set_delay(delay);
}

void DelaySimple::set_delay(MdFloat delay) noexcept {
    delay = utility::clip(delay, static_cast<MdFloat>(1), get_max_delay());

    this->m_delay = static_cast<std::uint32_t>(delay);
}

MdFloat DelaySimple::get_max_delay() noexcept {
    return this->m_max_delay;
}

MdFloat DelaySimple::read() noexcept {
    // Get the correct read position into the buffer
    auto phase = utility::wrap(this->m_write_index - this->m_delay, 0, this->m_upper_bound_1);

    return this->m_buffer[phase];
}
