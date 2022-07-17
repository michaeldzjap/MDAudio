#ifndef MD_AUDIO_TAP_UNINTERPOLATED_HPP
#define MD_AUDIO_TAP_UNINTERPOLATED_HPP

#include <cstddef>
#include "Unit.hpp"
#include "Writer.hpp"
#include "utility.hpp"

using md_audio::utility::clip;

namespace md_audio {

    template <class Allocator, class Reader>
    class TapUninterpolated : public Unit {
    public:
        TapUninterpolated(Writer<Allocator>& writer, Reader& reader, std::uint32_t max_delay_samples) :
            m_max_delay_samples(max_delay_samples),
            m_delay_samples(1),
            m_writer(writer),
            m_reader(reader)
        {}

        void set_delay_time(double delay_time) noexcept {
            auto delay_samples = clip<double>(
                m_sample_rate * delay_time, 1, m_max_delay_samples
            );

            m_delay_samples = static_cast<std::uint32_t>(delay_samples);
        }

        double read() noexcept {
            return m_reader.read(m_writer.m_write_index - m_delay_samples);
        }

    private:
        std::uint32_t m_max_delay_samples;
        std::uint32_t m_delay_samples;
        Writer<Allocator>& m_writer;
        Reader m_reader;
    };

}

#endif /* MD_AUDIO_TAP_UNINTERPOLATED_HPP */
