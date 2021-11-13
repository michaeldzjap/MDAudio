#ifndef MD_AUDIO_DELAY_INTERPOLATED_HPP
#define MD_AUDIO_DELAY_INTERPOLATED_HPP

#include <cstddef>
#include "Buffer.hpp"
#include "Unit.hpp"
#include "utility.hpp"
#include "Writer.hpp"

using md_audio::utility::clip;
using md_audio::utility::next_power_of_two;

namespace md_audio {

    template <class Allocator, class Reader>
    class DelayInterpolated : public Unit {
    public:
        explicit DelayInterpolated(Allocator &allocator, double max_delay_time) :
            m_max_delay_samples(m_sample_rate * max_delay_time),
            m_buffer(allocator, next_power_of_two(m_max_delay_samples)),
            m_writer(m_buffer),
            m_reader(m_buffer)
        {
            set_delay_time(0.);
        }

        explicit DelayInterpolated(Allocator &allocator, double max_delay_time, double delay_time) :
            m_max_delay_samples(m_sample_rate * max_delay_time),
            m_buffer(allocator, next_power_of_two(m_max_delay_samples)),
            m_writer(m_buffer),
            m_reader(m_buffer)
        {
            set_delay_time(delay_time);
        }

        bool initialise() noexcept {
            return m_buffer.initialise();
        }

        void set_delay_time(double delay_time) noexcept {
            auto delay_samples = clip<double>(m_sample_rate * delay_time, 1, m_max_delay_samples);

            m_delay_samples = static_cast<std::uint32_t>(delay_samples);
            m_frac = delay_samples - m_delay_samples;
        }

        virtual double process(double in) noexcept {
            auto z = m_reader.read(m_writer.m_write_index - m_delay_samples, m_frac);

            m_writer.write(in);

            return z;
        }

    private:
        std::uint32_t m_max_delay_samples;

    protected:
        std::uint32_t m_delay_samples;
        double m_frac;
        Buffer<Allocator> m_buffer;
        Writer<Allocator> m_writer;
        Reader m_reader;
    };

}

#endif /* MD_AUDIO_DELAY_INTERPOLATED_HPP */
