#ifndef MD_AUDIO_DELAY_STATIC_HPP
#define MD_AUDIO_DELAY_STATIC_HPP

#include "Delay.hpp"
#include "Reader.hpp"

namespace md_audio {

    template <class Allocator>
    class DelayStatic : public Delay<Allocator> {

        using Delay<Allocator>::m_buffer;
        using Delay<Allocator>::m_writer;
        using Delay<Allocator>::m_delay_samples;

    public:
        explicit DelayStatic(Allocator &allocator, double max_delay_time) :
            Delay<Allocator>(allocator, max_delay_time),
            m_reader(m_buffer)
        {}

        explicit DelayStatic(Allocator &allocator, double max_delay_time, double delay_time) :
            Delay<Allocator>(allocator, max_delay_time, delay_time),
            m_reader(m_buffer)
        {}

        double process(double in) noexcept {
            auto z = m_reader.read(m_writer.m_write_index - m_delay_samples);

            m_writer.write(in);

            return z;
        }

    private:
        Reader<Allocator> m_reader;
    };

}

#endif /* MD_AUDIO_DELAY_STATIC_HPP */
