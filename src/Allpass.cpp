#include "Allpass.hpp"

using md_audio::Allpass;
using md_audio::MdFloat;

Allpass::Allpass(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay) :
    Writer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_max_delay(max_delay)
{}

Allpass::Allpass(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay, MdFloat gain) :
    Writer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_max_delay(max_delay)
{
    set_gain(gain);
}
