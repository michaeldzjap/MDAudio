#include "Delay.hpp"

using md_audio::Delay;
using md_audio::MdFloat;

Delay::Delay(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay) :
    Writer(allocator, static_cast<std::uint32_t>(max_delay)),
    m_max_delay(max_delay)
{}

MdFloat Delay::perform(MdFloat in) noexcept {
    this->write(in);

    auto z = read();

    this->increment(); // Increment the write pointer

    return z;
}
