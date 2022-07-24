#ifndef MD_AUDIO_ALLPASS_HPP
#define MD_AUDIO_ALLPASS_HPP

#include <cstddef>
#include "Buffer.hpp"
#include "Unit.hpp"
#include "Writer.hpp"
#include "utility.hpp"

using md_audio::utility::clip;
using md_audio::utility::next_power_of_two;

namespace md_audio {

    template <class Allocator, class Reader, class Tap>
    class Allpass : public Unit {
    public:
        explicit Allpass(Allocator& allocator, double max_delay_time) :
            m_buffer(allocator, next_power_of_two<std::uint32_t>(m_sample_rate * max_delay_time)),
            m_writer(m_buffer),
            m_reader(m_buffer),
            m_tap(m_writer, m_reader, m_sample_rate * max_delay_time)
        {
            set_delay_time(0.);
            set_gain(0.);
        }

        explicit Allpass(Allocator& allocator, double max_delay_time, double delay_time) :
            m_buffer(allocator, next_power_of_two<std::uint32_t>(m_sample_rate * max_delay_time)),
            m_writer(m_buffer),
            m_reader(m_buffer),
            m_tap(m_writer, m_reader, m_sample_rate * max_delay_time)
        {
            set_delay_time(delay_time);
            set_gain(0.);
        }

        explicit Allpass(Allocator& allocator, double max_delay_time, double delay_time, double gain) :
            m_buffer(allocator, next_power_of_two<std::uint32_t>(m_sample_rate * max_delay_time)),
            m_writer(m_buffer),
            m_reader(m_buffer),
            m_tap(m_writer, m_reader, m_sample_rate * max_delay_time)
        {
            set_delay_time(delay_time);
            set_gain(gain);
        }

        bool initialise() noexcept {
            return m_buffer.initialise();
        }

        void set_delay_time(double delay_time) noexcept {
            m_tap.set_delay_time(delay_time);
        }

        void set_gain(double gain) noexcept {
            m_gain = clip(gain, 0., 1.);
        }

        double process(double in) noexcept {
            auto sd = m_tap.read();
            auto s = in + m_gain * sd;

            m_writer.write(s);

            return sd - m_gain * s;
        }

    private:
        Buffer<Allocator> m_buffer;
        Writer<Allocator> m_writer;
        Reader m_reader;
        Tap m_tap;
        double m_gain;
    };

}

#endif /* MD_AUDIO_ALLPASS_HPP */
