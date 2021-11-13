#ifndef MD_AUDIO_ALLPASS_INTERPOLATED_HPP
#define MD_AUDIO_ALLPASS_INTERPOLATED_HPP

#include "DelayInterpolated.hpp"
#include "Gainable.hpp"

namespace md_audio {

    template <class Allocator, class Reader>
    class AllpassInterpolated : public Gainable, public DelayInterpolated<Allocator, Reader> {

        using DelayInterpolated<Allocator, Reader>::m_delay_samples;
        using DelayInterpolated<Allocator, Reader>::m_frac;
        using DelayInterpolated<Allocator, Reader>::m_writer;
        using DelayInterpolated<Allocator, Reader>::m_reader;

    public:
        explicit AllpassInterpolated(Allocator& allocator, double max_delay_time) :
            DelayInterpolated<Allocator, Reader>(allocator, max_delay_time)
        {
            set_gain(0.);
        }

        explicit AllpassInterpolated(Allocator& allocator, double max_delay_time, double delay_time) :
            DelayInterpolated<Allocator, Reader>(allocator, max_delay_time, delay_time)
        {
            set_gain(0.);
        }

        explicit AllpassInterpolated(Allocator& allocator, double max_delay_time, double delay_time, double gain) :
            DelayInterpolated<Allocator, Reader>(allocator, max_delay_time, delay_time)
        {
            set_gain(gain);
        }

        double process(double in) noexcept override {
            auto sd = m_reader.read(m_writer.m_write_index - m_delay_samples, m_frac);
            auto s = in + m_gain * sd;

            m_writer.write(s);

            return sd - m_gain * s;
        }
    };

}

#endif /* MD_AUDIO_ALLPASS_INTERPOLATED_HPP */
