#include "TapDelayCubic.hpp"

using md_audio::MdFloat;
using md_audio::TapDelayCubic;

TapDelayCubic::TapDelayCubic(memory::Poolable& pool, std::size_t max_delay, std::size_t taps) :
    m_pool(pool),
    m_buffer(pool, max_delay),
    m_reader(m_buffer, max_delay - 1),
    m_writer(m_buffer, max_delay - 1),
    m_max_delay(static_cast<MdFloat>(max_delay - 2)),
    m_taps(taps)
{
    initialise();
}

void TapDelayCubic::initialise() {
    m_buffer.initialise();

    m_delay = static_cast<std::uint32_t*>(allocate(sizeof(std::uint32_t)));
    m_frac = static_cast<MdFloat*>(allocate(sizeof(MdFloat)));

    for (auto i = 0; i < m_taps; ++i)
        set_delay(i, static_cast<MdFloat>(1));
}

void* TapDelayCubic::allocate(std::size_t size) {
    auto memory = m_pool.allocate(m_taps * size);

    if (!memory) throw std::bad_alloc();

    return memory;
}

void TapDelayCubic::set_delay(const MdFloat* delay) noexcept {
    for (auto i = 0; i < m_taps; ++i) set_delay(i, delay[i]);
}

MdFloat* TapDelayCubic::perform(MdFloat in, MdFloat* out, std::size_t) noexcept {
    for (auto i = 0; i < m_taps; ++i)
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
