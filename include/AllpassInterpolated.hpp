#ifndef MD_AUDIO_ALLPASS_INTERPOLATED_HPP
#define MD_AUDIO_ALLPASS_INTERPOLATED_HPP

#include "DelayInterpolated.hpp"

namespace md_audio {

    template <class Allocator, class Reader>
    class AllpassInterpolated : public DelayInterpolated<Allocator, Reader> {

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

        void set_gain(double gain) noexcept {
            m_gain = clip(gain, 0., 1.);
        }

        double process(double in) noexcept {
            auto sd = m_reader.read(m_writer.m_write_index - m_delay_samples, m_frac);
            auto s = in + m_gain * sd;

            m_writer.write(s);

            return sd - m_gain * s;
        }

    private:
        double m_gain;
    };

}

#endif /* MD_AUDIO_ALLPASS_INTERPOLATED_HPP */
