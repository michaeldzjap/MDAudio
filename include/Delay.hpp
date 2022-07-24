#ifndef MD_AUDIO_DELAY_HPP
#define MD_AUDIO_DELAY_HPP

#include <cstddef>
#include "Buffer.hpp"
#include "Unit.hpp"
#include "Writer.hpp"
#include "utility.hpp"

using md_audio::utility::next_power_of_two;

namespace md_audio {

    template <class Allocator, class Reader, class Tap>
    class Delay : public Unit {
    public:
        explicit Delay(Allocator &allocator, double max_delay_time) :
            m_buffer(allocator, next_power_of_two<std::uint32_t>(m_sample_rate * max_delay_time)),
            m_writer(m_buffer),
            m_reader(m_buffer),
            m_tap(m_writer, m_reader, m_sample_rate * max_delay_time)
        {
            set_delay_time(0.);
        }

        explicit Delay(Allocator &allocator, double max_delay_time, double delay_time) :
            m_buffer(allocator, next_power_of_two<std::uint32_t>(m_sample_rate * max_delay_time)),
            m_writer(m_buffer),
            m_reader(m_buffer),
            m_tap(m_writer, m_reader, m_sample_rate * max_delay_time)
        {
            set_delay_time(delay_time);
        }

        bool initialise() noexcept {
            return m_buffer.initialise();
        }

        void set_delay_time(double delay_time) noexcept {
            m_tap.set_delay_time(delay_time);
        }

        double process(double in) noexcept {
            auto z = m_tap.read();

            m_writer.write(in);

            return z;
        }

    private:
        Buffer<Allocator> m_buffer;
        Writer<Allocator> m_writer;
        Reader m_reader;
        Tap m_tap;
    };

}

#endif /* MD_AUDIO_DELAY_HPP */
