#include "Reverb.hpp"
#include "ReverbConfig.hpp"
#include "ReversibleDelay.hpp"
#include "StaticPool.hpp"
#include "TapDelayCubic.hpp"
#include "TapDelayLinear.hpp"
#include "TapDelayStatic.hpp"
#include "WhiteNoise.hpp"
#include "types.hpp"
#include <iomanip>
#include <iostream>

template <std::size_t Size>
using Pool = md_audio::memory::StaticPool<Size>;

int main() {
    std::cout << std::fixed;
    std::cout << std::setprecision(4);

    constexpr auto MAX_DELAY = 102;
    constexpr auto MAX_DELAY_SIZE = MAX_DELAY * sizeof(md_audio::MdFloat);
    constexpr auto TAPS = 4;
    constexpr auto TAPS_SIZE = TAPS * (sizeof(std::uint32_t) + sizeof(md_audio::MdFloat));
    constexpr auto TOTAL_SIZE = MAX_DELAY_SIZE + TAPS_SIZE;
    constexpr md_audio::MdFloat DELAY_TIMES[TAPS] = {99.725535, 50., 5.123, 25.56256};

    Pool<TOTAL_SIZE> pool;

    md_audio::TapDelayCubic delay(pool, 102.f, TAPS);
    md_audio::WhiteNoise noise;

    delay.initialise();
    delay.set_delay(DELAY_TIMES);

    for (std::size_t i = 0; i < 441; ++i) {
        md_audio::MdFloat z[TAPS];

        const auto y = noise.perform();
        delay.perform(y, z, TAPS);

        std::cout << i << "\t";

        for (auto i = 0; i < TAPS; i++)
            std::cout << z[i] << ", ";

        std::cout << std::endl;
    }
}
