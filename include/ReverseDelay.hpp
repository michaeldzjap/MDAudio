#ifndef MD_AUDIO_REVERSE_DELAY_HPP
#define MD_AUDIO_REVERSE_DELAY_HPP

#include "Buffer.hpp"
#include "HannOscillator.hpp"
#include "Phasor.hpp"
#include "ReaderLinear.hpp"
#include "TapInterpolated.hpp"
#include "Unit.hpp"
#include "Writer.hpp"
#include "constants.hpp"
#include "utility.hpp"

using md_audio::utility::clip;
using md_audio::utility::make_array;
using md_audio::utility::next_power_of_two;

namespace md_audio {

    template <class Allocator, std::size_t OVERLAP = 2, class Reader = ReaderLinear<Allocator>>
    class ReverseDelay : public Unit {
    public:
        explicit ReverseDelay(Allocator& allocator, double max_size, double size) :
            m_buffer(allocator, next_power_of_two<std::uint32_t>(m_sample_rate * max_size)),
            m_writer(m_buffer),
            m_reader(m_buffer),
            m_taps(make_array<OVERLAP>(TapInterpolated(m_writer, m_reader, m_sample_rate * max_size))),
            m_max_size(max_size),
            m_norm(2. / OVERLAP)
        {
            set_size(size);
        }

        bool initialise() noexcept {
            auto result = m_buffer.initialise();

            if (!result) return result;

            for (std::size_t i = 0; i < OVERLAP; ++i) {
                m_phasor[i].set_phase(static_cast<double>(i) / OVERLAP);
                m_osc[i].set_frequency(0.);
            }

            return result;
        }

        void set_size(double size) noexcept {
            m_size = clip(size, .01, m_max_size);

            set_frequency();
        }

        double process(double in) noexcept {
            auto z = 0.;

            for (std::size_t i = 0; i < OVERLAP; ++i) {
                auto phase = m_phasor[i].process();

                m_osc[i].set_phase(phase * TWO_PI);

                auto window = m_osc[i].process();

                m_taps[i].set_delay_time(phase * m_size);

                z += m_taps[i].read() * window;
            }

            m_writer.write(in);

            return z * m_norm;
        }

    private:
        std::array<Phasor, OVERLAP> m_phasor;
        std::array<HannOscillator, OVERLAP> m_osc;
        Buffer<Allocator> m_buffer;
        Writer<Allocator> m_writer;
        Reader m_reader;
        std::array<TapInterpolated<Allocator, Reader>, OVERLAP> m_taps;
        const double m_max_size;
        const double m_norm;
        double m_size;

        void set_frequency() noexcept {
            auto frequency = 2. / m_size;

            for (std::size_t i = 0; i < OVERLAP; ++i)
                m_phasor[i].set_frequency(frequency);
        }
    };

}

#endif /* MD_AUDIO_REVERSE_DELAY_HPP */
