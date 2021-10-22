#ifndef MD_AUDIO_DELAY_CUBIC_HPP
#define MD_AUDIO_DELAY_CUBIC_HPP

#include <cstddef>
#include "Buffer.hpp"
#include "ReaderCubic.hpp"
#include "Unit.hpp"
#include "utility.hpp"
#include "Writer.hpp"

using md_audio::utility::clip;
using md_audio::utility::next_power_of_two;

namespace md_audio {

    template <class Allocator>
    class DelayCubic : public Unit {
    public:
        explicit DelayCubic(Allocator &allocator, MdFloat max_delay_time) :
            m_max_delay_samples(m_sample_rate * max_delay_time),
            m_buffer(allocator, next_power_of_two(m_max_delay_samples)),
            m_reader(m_buffer),
            m_writer(m_buffer)
        {
            set_delay_time(.0);
        }

        explicit DelayCubic(Allocator &allocator, MdFloat max_delay_time, MdFloat delay_time) :
            m_max_delay_samples(m_sample_rate * max_delay_time),
            m_buffer(allocator, next_power_of_two(m_max_delay_samples)),
            m_reader(m_buffer),
            m_writer(m_buffer)
        {
            set_delay_time(delay_time);
        }

        void set_delay_time(MdFloat delay_time) noexcept {
            auto delay_samples = clip<MdFloat>(m_sample_rate * delay_time, 1, m_max_delay_samples);

            m_delay_samples = static_cast<std::uint32_t>(delay_samples);
            m_frac = delay_samples - m_delay_samples;
        }

        bool initialise() noexcept {
            return m_buffer.initialise();
        }

        MdFloat process(MdFloat in) noexcept {
            auto z = m_reader.read(m_writer.m_write_index - m_delay_samples, m_frac);

            m_writer.write(in);

            return z;
        }

    private:
        std::uint32_t m_max_delay_samples;
        std::uint32_t m_delay_samples;
        MdFloat m_frac;
        Buffer<Allocator> m_buffer;
        ReaderCubic<Allocator> m_reader;
        Writer<Allocator> m_writer;
    };

}

#endif /* MD_AUDIO_DELAY_CUBIC_HPP */
