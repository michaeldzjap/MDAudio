#include "TapDelayCubic.hpp"

using md_audio::MdFloat;
using md_audio::TapDelayCubic;

TapDelayCubic::TapDelayCubic(memory::Poolable& pool, MdFloat max_delay, std::size_t taps) :
    m_max_delay(utility::ceil(m_sample_rate * max_delay)),
    m_taps(taps),
    m_pool(pool),
    m_buffer(pool, m_max_delay),
    m_reader(m_buffer, m_max_delay - 1),
    m_writer(m_buffer, m_max_delay - 1)
{
    initialise();
}

void TapDelayCubic::initialise() {
    m_delay = static_cast<std::uint32_t*>(m_pool.allocate(m_taps * sizeof(std::uint32_t)));
    m_frac = static_cast<MdFloat*>(m_pool.allocate(m_taps * sizeof(MdFloat)));

    for (std::uint32_t i = 0; i < m_taps; ++i)
        set_delay(i, static_cast<MdFloat>(1));
}

void TapDelayCubic::set_delay(const MdFloat* delay) noexcept {
    for (std::uint32_t i = 0; i < m_taps; ++i) set_delay(i, delay[i]);
}

MdFloat* TapDelayCubic::perform(MdFloat in, MdFloat* out, std::size_t) noexcept {
    for (std::uint32_t i = 0; i < m_taps; ++i)
        out[i] = m_reader.read(m_writer, m_delay[i], m_frac[i]);

    m_writer.write(in);

    return out;
}

void TapDelayCubic::write(MdFloat in) noexcept {
    m_writer.write(in);
}

MdFloat TapDelayCubic::read(std::size_t index) noexcept {
    return m_reader.read(m_writer, m_delay[index], m_frac[index]);
}

TapDelayCubic::~TapDelayCubic() {
    if (m_delay) m_pool.deallocate(m_delay);
    if (m_frac) m_pool.deallocate(m_frac);
}
