#ifndef MD_AUDIO_TAP_DELAY_INTERPOLATED_HPP
#define MD_AUDIO_TAP_DELAY_INTERPOLATED_HPP

#include <array>
#include <cstddef>
#include "Buffer.hpp"
#include "Unit.hpp"
#include "Writer.hpp"
#include "utility.hpp"

using md_audio::utility::clip;
using md_audio::utility::next_power_of_two;

namespace md_audio {

    template <class Allocator, class Reader, std::size_t TAPS = 2>
    class TapDelayInterpolated : public Unit {
    public:
        explicit TapDelayInterpolated(Allocator& allocator, double max_delay_time) :
            m_max_delay_samples(m_sample_rate * max_delay_time),
            m_buffer(allocator, next_power_of_two(m_max_delay_samples)),
            m_writer(m_buffer),
            m_reader(m_buffer)
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
            m_reader(m_buffer)
        {
            set_delay_time(delay_times);
        }

        bool initialise() noexcept {
            return m_buffer.initialise();
        }

        void set_delay_time(std::array<double, TAPS>& delay_times) noexcept {
            for (std::size_t i = 0; i < TAPS; ++i) {
                auto delay_samples = clip<double>(
                    m_sample_rate * delay_times[i], 1, m_max_delay_samples
                );

                m_delay_samples[i] = static_cast<std::uint32_t>(delay_samples);
                m_frac[i] = delay_samples - m_delay_samples[i];
            }
        }

        std::array<double, TAPS> process(double in) noexcept {
            std::array<double, TAPS> out;

            for (std::size_t i = 0; i < TAPS; ++i)
                out[i] = m_reader.read(
                    m_writer.m_write_index - m_delay_samples[i], m_frac[i]
                );

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
    };

}

#endif /* MD_AUDIO_TAP_DELAY_INTERPOLATED_HPP */
