#include "DelayLinear.hpp"
#include "utility.hpp"

using md_audio::DelayLinear;
using md_audio::MdFloat;

DelayLinear::DelayLinear(memory::Poolable& pool, MdFloat max_delay) :
    m_buffer(pool, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay - static_cast<MdFloat>(1))
{
    set_delay(static_cast<MdFloat>(1));
}

DelayLinear::DelayLinear(memory::Poolable& pool, MdFloat max_delay, MdFloat delay) :
    m_buffer(pool, static_cast<std::uint32_t>(max_delay)),
    m_reader(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
    m_max_delay(max_delay - static_cast<MdFloat>(1))
{
    set_delay(delay);
}

void DelayLinear::initialise() {
    m_buffer.initialise();
}

MdFloat DelayLinear::perform(MdFloat in) noexcept {
    m_writer.write(in);

    auto z = m_reader.read(m_writer, m_delay, m_frac);

    return z;
}
