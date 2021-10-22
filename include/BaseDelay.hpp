#ifndef MD_AUDIO_BASE_DELAY_HPP
#define MD_AUDIO_BASE_DELAY_HPP

#include <cstddef>
#include "Buffer.hpp"
#include "types.hpp"
#include "Unit.hpp"
#include "utility.hpp"
#include "Writer.hpp"

using md_audio::utility::clip;
using md_audio::utility::next_power_of_two;

namespace md_audio {

    template <class Allocator>
    class BaseDelay : public Unit {
    public:
        explicit BaseDelay(Allocator &allocator, MdFloat max_delay_time) :
            m_max_delay_samples(m_sample_rate * max_delay_time),
            m_buffer(allocator, next_power_of_two(m_max_delay_samples)),
            m_writer(m_buffer)
        {
            set_delay_time(.0);
        }

        explicit BaseDelay(Allocator &allocator, MdFloat max_delay_time, MdFloat delay_time) :
            m_max_delay_samples(m_sample_rate * max_delay_time),
            m_buffer(allocator, next_power_of_two(m_max_delay_samples)),
            m_writer(m_buffer)
        {
            set_delay_time(delay_time);
        }

        bool initialise() noexcept {
            return m_buffer.initialise();
        }

        void set_delay_time(MdFloat delay_time) noexcept {
            auto delay_samples = clip<MdFloat>(m_sample_rate * delay_time, 1, m_max_delay_samples);

            m_delay_samples = static_cast<std::uint32_t>(delay_samples);
        }

    private:
        std::uint32_t m_max_delay_samples;

    protected:
        std::uint32_t m_delay_samples;
        Buffer<Allocator> m_buffer;
        Writer<Allocator> m_writer;
    };

}

#endif /* MD_AUDIO_BASE_DELAY_HPP */
