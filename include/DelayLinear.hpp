#ifndef MD_AUDIO_DELAY_LINEAR_HPP
#define MD_AUDIO_DELAY_LINEAR_HPP

#include "DelayInterpolated.hpp"
#include "ReaderLinear.hpp"

namespace md_audio {

    template <class Allocator>
    class DelayLinear : public DelayInterpolated<Allocator> {

        using DelayInterpolated<Allocator>::m_buffer;
        using DelayInterpolated<Allocator>::m_writer;
        using DelayInterpolated<Allocator>::m_delay_samples;
        using DelayInterpolated<Allocator>::m_frac;

    public:
        explicit DelayLinear(Allocator &allocator, double max_delay_time) :
            DelayInterpolated<Allocator>(allocator, max_delay_time),
            m_reader(m_buffer)
        {}

        explicit DelayLinear(Allocator &allocator, double max_delay_time, double delay_time) :
            DelayInterpolated<Allocator>(allocator, max_delay_time, delay_time),
            m_reader(m_buffer)
        {}

        double process(double in) noexcept {
            auto z = m_reader.read(m_writer.m_write_index - m_delay_samples, m_frac);

            m_writer.write(in);

            return z;
        }

    private:
        ReaderLinear<Allocator> m_reader;
    };

}

#endif /* MD_AUDIO_DELAY_LINEAR_HPP */
