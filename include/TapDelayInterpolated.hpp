#ifndef MD_AUDIO_TAP_DELAY_INTERPOLATED_HPP
#define MD_AUDIO_TAP_DELAY_INTERPOLATED_HPP

#include <array>
#include <cstddef>
#include "Buffer.hpp"
#include "TapInterpolated.hpp"
#include "Unit.hpp"
#include "Writer.hpp"
#include "utility.hpp"

using md_audio::utility::make_array;
using md_audio::utility::next_power_of_two;

namespace md_audio {

    template <class Allocator, class Reader, std::size_t TAPS = 2>
    class TapDelayInterpolated : public Unit {
    public:
        explicit TapDelayInterpolated(Allocator& allocator, double max_delay_time) :
            m_max_delay_samples(m_sample_rate * max_delay_time),
            m_buffer(allocator, next_power_of_two(m_max_delay_samples)),
            m_writer(m_buffer),
            m_reader(m_buffer),
            m_taps(make_array<TAPS>(TapInterpolated(m_writer, m_reader, m_max_delay_samples)))
        {
            std::array<double, TAPS> delay_times { 0. };

            set_delay_time(delay_times);
        }

        explicit TapDelayInterpolated(
            Allocator& allocator, double max_delay_time, std::array<double, TAPS>& delay_times
        ) :
            m_max_delay_samples(m_sample_rate * max_delay_time),
            m_buffer(allocator, next_power_of_two(m_max_delay_samples)),
            m_writer(m_buffer),
            m_reader(m_buffer),
            m_taps(make_array<TAPS>(TapInterpolated(m_writer, m_reader, m_max_delay_samples)))
        {
            set_delay_time(delay_times);
        }

        bool initialise() noexcept {
            return m_buffer.initialise();
        }

        void set_delay_time(std::array<double, TAPS>& delay_times) noexcept {
            for (std::size_t i = 0; i < TAPS; ++i)
                m_taps[i].set_delay_time(delay_times[i]);
        }

        std::array<double, TAPS> process(double in) noexcept {
            std::array<double, TAPS> out;

            for (std::size_t i = 0; i < TAPS; ++i)
                out[i] = m_taps[i].read();

            m_writer.write(in);

            return out;
        }

    private:
        std::uint32_t m_max_delay_samples;
        std::array<std::uint32_t, TAPS> m_delay_samples;
        std::array<double, TAPS> m_frac;
        Buffer<Allocator> m_buffer;
        Writer<Allocator> m_writer;
        Reader m_reader;
        std::array<TapInterpolated<Allocator, Reader>, TAPS> m_taps;
    };

}

#endif /* MD_AUDIO_TAP_DELAY_INTERPOLATED_HPP */
