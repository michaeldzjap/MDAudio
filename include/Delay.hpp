#ifndef MD_AUDIO_DELAY_HPP
#define MD_AUDIO_DELAY_HPP

#include "BaseDelay.hpp"
#include "Reader.hpp"

namespace md_audio {

    template <class Allocator>
    class Delay : public BaseDelay<Allocator> {

        using BaseDelay<Allocator>::m_buffer;
        using BaseDelay<Allocator>::m_writer;
        using BaseDelay<Allocator>::m_delay_samples;

    public:
        explicit Delay(Allocator &allocator, MdFloat max_delay_time) :
            BaseDelay<Allocator>(allocator, max_delay_time),
            m_reader(m_buffer)
        {}

        explicit Delay(Allocator &allocator, MdFloat max_delay_time, MdFloat delay_time) :
            BaseDelay<Allocator>(allocator, max_delay_time, delay_time),
            m_reader(m_buffer)
        {}

        MdFloat process(MdFloat in) noexcept {
            auto z = m_reader.read(m_writer.m_write_index - m_delay_samples);

            m_writer.write(in);

            return z;
        }

    private:
        Reader<Allocator> m_reader;
    };

}

#endif /* MD_AUDIO_DELAY_HPP */
