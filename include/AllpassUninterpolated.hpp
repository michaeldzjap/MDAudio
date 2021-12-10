#ifndef MD_AUDIO_ALLPASS_UNINTERPOLATED_HPP
#define MD_AUDIO_ALLPASS_UNINTERPOLATED_HPP

#include "DelayUninterpolated.hpp"
#include "Gainable.hpp"

namespace md_audio {

    template <class Allocator, class Reader>
    class AllpassUninterpolated : public Gainable, public DelayUninterpolated<Allocator, Reader> {

        using DelayUninterpolated<Allocator, Reader>::m_delay_samples;
        using DelayUninterpolated<Allocator, Reader>::m_writer;
        using DelayUninterpolated<Allocator, Reader>::m_reader;

    public:
        explicit AllpassUninterpolated(Allocator& allocator, double max_delay_time) :
            DelayUninterpolated<Allocator, Reader>(allocator, max_delay_time)
        {
            set_gain(0.);
        }

        explicit AllpassUninterpolated(Allocator& allocator, double max_delay_time, double delay_time) :
            DelayUninterpolated<Allocator, Reader>(allocator, max_delay_time, delay_time)
        {
            set_gain(0.);
        }

        explicit AllpassUninterpolated(Allocator& allocator, double max_delay_time, double delay_time, double gain) :
            DelayUninterpolated<Allocator, Reader>(allocator, max_delay_time, delay_time)
        {
            set_gain(gain);
        }

        double process(double in) noexcept override {
            auto sd = m_reader.read(m_writer.m_write_index - m_delay_samples);
            auto s = in + m_gain * sd;

            m_writer.write(s);

            return sd - m_gain * s;
        }
    };

}

#endif /* MD_AUDIO_ALLPASS_UNINTERPOLATED_HPP */