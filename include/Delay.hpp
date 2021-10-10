#ifndef MD_AUDIO_DELAY_HPP
#define MD_AUDIO_DELAY_HPP

#include <cstddef>
#include "Buffer.hpp"
#include "Reader.hpp"
#include "Unit.hpp"
#include "utility.hpp"
#include "Writer.hpp"

using md_audio::utility::clip;
using md_audio::utility::next_power_of_two;

namespace md_audio {

    template <class Allocator>
    class Delay : public Unit {
    public:
        explicit Delay(Allocator &allocator, MdFloat max_delay) :
            m_max_delay(m_sample_rate * max_delay),
            m_buffer(allocator, next_power_of_two(m_max_delay)),
            m_reader(m_buffer),
            m_writer(m_buffer)
        {
            set_delay(.0);
        }

        explicit Delay(Allocator &allocator, MdFloat max_delay, MdFloat delay) :
            m_max_delay(m_sample_rate * max_delay),
            m_buffer(allocator, next_power_of_two(m_max_delay)),
            m_reader(m_buffer),
            m_writer(m_buffer)
        {
            set_delay(delay);
        }

        bool initialise() noexcept {
            return m_buffer.initialise();
        }

        void set_delay(MdFloat delay) noexcept {
            delay = clip<MdFloat>(m_sample_rate * delay, 1, m_max_delay);

            m_delay = static_cast<std::uint32_t>(delay);
        }

        MdFloat process(MdFloat in) noexcept {
            auto z = m_reader.read(m_writer.m_write_index - m_delay);

            m_writer.write(in);

            return z;
        }

    private:
        std::uint32_t m_max_delay;
        std::uint32_t m_delay;
        Buffer<Allocator> m_buffer;
        Reader<Allocator> m_reader;
        Writer<Allocator> m_writer;
    };

}

#endif /* MD_AUDIO_DELAY_HPP */
