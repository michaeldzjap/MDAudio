#include "Taus88.hpp"
#include <chrono>
#include <limits>

using md_audio::Taus88;

Taus88::Taus88() {
    auto now = std::chrono::high_resolution_clock::now();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());

    initialise(seconds.count());
}

Taus88::Taus88(std::int32_t seed) {
    initialise(seed);
}

void Taus88::initialise(std::int32_t seed) noexcept {
    seed = static_cast<std::uint32_t>(Hash(seed));

    m_s1 = 1243598713u ^ seed;
    if (m_s1 <  2) m_s1 = 1243598713u;

    m_s2 = 3093459404u ^ seed;
    if (m_s2 <  8) m_s2 = 3093459404u;

    m_s3 = 1821928721u ^ seed;
    if (m_s3 < 16) m_s3 = 1821928721u;
}

double Taus88::generate() noexcept {
    return static_cast<double>(trand(m_s1, m_s2, m_s3))
        / static_cast<double>(std::numeric_limits<std::uint32_t>::max())
        * 2. - 1.;
}
