#include "Normaliser.hpp"
#include <cstring>

using md_audio::MdFloat;
using md_audio::Normaliser;

Normaliser::Normaliser(memory::Poolable& pool, std::uint32_t duration) :
    m_pool(pool),
    m_size(3 * duration),
    m_duration(duration),
    m_slope_factor(static_cast<MdFloat>(1) / static_cast<MdFloat>(duration))
{
    set_amplitude(static_cast<MdFloat>(1));
}

Normaliser::Normaliser(memory::Poolable& pool, std::uint32_t duration, MdFloat amplitude) :
    m_pool(pool),
    m_size(3 * duration),
    m_duration(duration),
    m_slope_factor(static_cast<MdFloat>(1) / static_cast<MdFloat>(duration))
{
    set_amplitude(amplitude);
}

void Normaliser::initialise() {
    auto memory = m_pool.allocate(m_size * sizeof(MdFloat));

    if (!memory) throw std::bad_alloc();

    m_memory = static_cast<MdFloat*>(memory);

    std::memset(m_memory, 0, m_size * sizeof(MdFloat));

    m_in_buf = m_memory;
    m_mid_buf = m_in_buf + m_duration;
    m_out_buf = m_mid_buf + m_duration;
}

MdFloat Normaliser::perform(MdFloat in) noexcept {
    MdFloat* in_buf = m_in_buf + m_pos;
    MdFloat* out_buf = m_out_buf + m_pos;

    (*(in_buf)++) = in;

    auto z = m_flips >= 2 ? m_level * (*(out_buf)++) : static_cast<MdFloat>(0);

    m_level += m_slope;
    in = std::abs(in);

    if (in > m_cur_max_val) m_cur_max_val = in;

    m_pos++;

    if (m_pos >= m_duration) {
        m_pos = 0;

        auto max_val_2 = utility::max(m_prev_max_val, m_cur_max_val);
        m_prev_max_val = m_cur_max_val;
        m_cur_max_val = static_cast<MdFloat>(0);

        auto next_level = max_val_2 <= static_cast<MdFloat>(0.00001)
            ? static_cast<MdFloat>(100000) * m_amplitude
            : m_amplitude / max_val_2;

        m_slope = (next_level - m_level) * m_slope_factor;

        auto temp = m_out_buf;
        m_out_buf = m_mid_buf;
        m_mid_buf = m_in_buf;
        m_in_buf = temp;

        m_flips++;
    }

    return z;
}

Normaliser::~Normaliser() {
    if (m_memory) m_pool.deallocate(m_memory);
}
