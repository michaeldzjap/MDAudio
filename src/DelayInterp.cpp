#include "DelayInterp.hpp"

using md_audio::DelayInterp;
using md_audio::MdFloat;

DelayInterp::DelayInterp(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay) :
    Delay(allocator, max_delay)
{}

void DelayInterp::set_delay(MdFloat delay) noexcept {
    delay = utility::clip(delay, static_cast<MdFloat>(1), this->get_max_delay());

    this->m_delay = static_cast<std::uint32_t>(delay);

    m_frac = delay - static_cast<MdFloat>(this->m_delay);
}

DelayInterp::~DelayInterp() {}
