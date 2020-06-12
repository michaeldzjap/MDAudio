#ifndef MD_AUDIO_DELAY_STATIC_HPP
#define MD_AUDIO_DELAY_STATIC_HPP

#include "Buffer.hpp"
#include "Reader.hpp"
#include "Writer.hpp"
#include "interfaces/Processable.hpp"
#include "utility.hpp"

namespace md_audio {

    class DelayStatic : public Processable<MdFloat, MdFloat> {
    public:
        explicit DelayStatic(memory::Poolable&, std::size_t);

        explicit DelayStatic(memory::Poolable&, std::size_t, MdFloat);

        inline void set_delay(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        Buffer m_buffer;
        Reader m_reader;
        Writer m_writer;
        MdFloat m_max_delay;
        std::uint32_t m_delay;
    };

    void DelayStatic::set_delay(MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), m_max_delay);

        m_delay = static_cast<std::uint32_t>(delay);
    }

}

#endif /* MD_AUDIO_DELAY_STATIC_HPP */
