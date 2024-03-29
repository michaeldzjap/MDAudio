#ifndef MD_AUDIO_UTILITY_HPP
#define MD_AUDIO_UTILITY_HPP

#include <array>
#include <cmath>
#include <cstdint>
#include <type_traits>
#include <utility>
#include "tables.hpp"

namespace md_audio::utility {

    template <typename T>
    using IsFloat = std::enable_if_t<std::is_floating_point<T>::value, T>;

    template <typename T>
    using IsInt = std::enable_if_t<std::is_integral<T>::value, T>;

    template <typename T>
    using IsFloatOrInt = std::enable_if_t<std::is_floating_point<T>::value || std::is_integral<T>::value, T>;

    template <typename T>
    inline constexpr IsFloatOrInt<T> max(const T a, const T b) noexcept {
        return a > b ? a : b;
    }

    template <typename T>
    inline constexpr IsFloatOrInt<T> min(const T a, const T b) noexcept {
        return a < b ? a : b;
    }

    template <typename T>
    inline constexpr IsFloatOrInt<T> clip(const T value, const T min, const T max) noexcept {
        // Clip value when it is outside of the allowed range
        if (value < min) return min;
        if (value > max) return max;

        return value;
    }

    inline constexpr auto wrap(std::int32_t value, const std::int32_t lo, const std::int32_t hi) noexcept {
        auto range = hi - lo + 1;

        value = (value - lo) % range;

        if (value < 0) return hi + 1 + value;

        return lo + value;
    }

    template <typename T>
    inline constexpr IsFloat<T> wrap(T value, const T lo, const T hi) noexcept {
        T range = static_cast<T>(0);

        if (value >= hi) {
            range = hi - lo;
            value -= range;
            if (value < hi) return value;
        } else if (value < lo) {
            range = hi - lo;
            value += range;
            if (value >= lo) return value;
        } else
            return value;

        if (hi == lo) return lo;

        return value - range * std::floor((value - lo) / range);
    }

    template <typename T>
    inline constexpr IsFloat<T> lin_lin(const T value, const T in_min, const T in_max,
        const T out_min, const T out_max) noexcept {
        if (value <= in_min) return out_min;
        if (value >= in_max) return out_max;

        return (value - in_min) / (in_max - in_min) * (out_max - out_min) + out_min;
    }

    template <typename T>
    inline constexpr IsFloat<T> lin_exp(const T value, const T in_min, const T in_max,
        const T out_min, const T out_max) noexcept {
        if (value <= in_min) return out_min;
        if (value >= in_max) return out_max;

        return std::pow(out_max / out_min, (value - in_min) / (in_max - in_min)) * out_min;
    }

    template <typename T>
    inline constexpr IsFloat<T> exp_lin(const T value, const T in_min, const T in_max,
        const T out_min, const T out_max) noexcept {
        if (value <= in_min) return out_min;
        if (value >= in_max) return out_max;

        return std::log(value / in_min) / std::log(in_max / in_min) * (out_max - out_min) + out_min;
    }

    template <typename T>
    inline constexpr IsFloat<T> lin_curve(const T value, const T in_min, const T in_max,
        const T out_min, const T out_max, const T curve = static_cast<T>(-4.)) noexcept {
        if (value <= in_min) return out_min;
        if (value >= in_max) return out_max;

        if (std::abs(curve) < static_cast<T>(0.001))
            lin_lin(value, in_min, in_max, out_min, out_max);

        auto grow = std::exp(curve);
        auto a = (out_max - out_min) / (static_cast<T>(1.) - grow);
        auto b = out_min + a;
        auto scaled = (value - in_min) / (in_max - in_min);

        return b - a * std::pow(grow, scaled);
    }

    template <typename T>
    inline constexpr IsFloat<T> curve_lin(const T value, const T in_min, const T in_max,
        const T out_min, const T out_max, const T curve = static_cast<T>(-4.)) noexcept {
        if (value <= in_min) return out_min;
        if (value >= in_max) return out_max;

        if (std::abs(curve) < static_cast<T>(0.001))
            lin_lin(value, in_min, in_max, out_min, out_max);

        auto grow = std::exp(curve);
        auto a = (in_max - in_min) / (static_cast<T>(1.) - grow);
        auto b = in_min + a;

        return std::log((b - value) / a) * (out_max - out_min) / curve + out_min;
    }

    template <typename T>
    inline constexpr IsFloat<T> interpolate_linear(const T x, const T a, const T b) noexcept {
        return a + x * (b - a);
    }

    /**
     * Cubic interpolation using 3rd order Hermite polynomial.
     */
    template <typename T>
    inline constexpr IsFloat<T> interpolate_cubic(const T x, const T y0, const T y1, const T y2, const T y3) noexcept {
        auto c0 = y1;
        auto c1 = .5 * (y2 - y0);
        auto c2 = y0 - 2.5 * y1 + 2. * y2 - .5 * y3;
        auto c3 = .5 * (y3 - y0) + 1.5 * (y1 - y2);

        return ((c3 * x + c2) * x + c1) * x + c0;
    }

    template <typename T>
    inline constexpr IsInt<T> next_power_of_two(T n) noexcept {
        if (n < 2) return 2;

        std::size_t i = 1;

        for (n--; i < sizeof(n) * 8; i <<= 1)
            n |= n >> i;

        return ++n;
    }

    template <typename T>
    inline constexpr IsFloat<T> lookup(const std::array<T, TABLE_SIZE + 1> &table, double phase) noexcept {
        auto index = static_cast<std::uint32_t>(phase);
        double frac = phase - static_cast<double>(index);
        auto y0 = table[index];
        auto y1 = table[index + 1];

        return y0 + frac * (y1 - y0);
    }

    template <typename T>
    inline constexpr double seconds_to_samples(const T delay_time, const T sample_rate) noexcept {
        return static_cast<T>(ceil(delay_time * sample_rate));
    }

    template <typename T, std::size_t N>
    inline constexpr std::array<IsFloat<T>, N> seconds_to_samples(const std::array<T, N>& in,
        const T sample_rate, const T margin = 0) noexcept {
        std::array<T, N> out{};

        for (std::uint32_t i = 0; i < N; ++i)
            out[i] = utility::seconds_to_samples(in[i], sample_rate) + margin;

        return out;
    }

    template <typename T, std::size_t N, std::size_t M>
    constexpr std::array<std::array<IsFloat<T>, M>, N> seconds_to_samples(
        const std::array<std::array<T, M>, N>& in,
        const T sample_rate,
        const T margin = 0
    ) noexcept {
        std::array<std::array<T, M>, N> out{};

        for (std::uint32_t i = 0; i < N; ++i)
            out[i] = seconds_to_samples(in[i], sample_rate, margin);

        return out;
    }

    template <typename T>
    inline constexpr IsFloat<T> midi_ratio(T midi) noexcept {
        return std::pow(static_cast<T>(2), midi / static_cast<T>(12));
    }

    template <typename T, std::size_t Size>
    inline constexpr IsFloatOrInt<T> sum(const std::array<T, Size>& arr) noexcept {
        auto sum = static_cast<T>(0);

        for (const auto& item : arr)
            sum += item;

        return sum;
    }

    template <typename T, std::size_t ...Is>
    inline constexpr std::array<T, sizeof...(Is)> make_array(const T& def, std::index_sequence<Is...>) noexcept {
        return {{(static_cast<void>(Is), def)...}};
    }

    template <std::size_t N, typename T>
    inline constexpr std::array<T, N> make_array(const T& def) noexcept {
        return make_array(def, std::make_index_sequence<N>());
    }

}

#endif /* MD_AUDIO_UTILITY_HPP */
