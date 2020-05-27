#ifndef MD_AUDIO_DELAY_STATIC_HPP
#define MD_AUDIO_DELAY_STATIC_HPP

#include "Buffer.hpp"
#include "Delayable.hpp"
#include "Reader.hpp"
#include "Writer.hpp"
#include "utility.hpp"

namespace md_audio {

    class DelayStatic : public Delayable {
    public:
        explicit DelayStatic(memory::Poolable&, MdFloat);

        explicit DelayStatic(memory::Poolable&, MdFloat, MdFloat);

        void initialise() override final;

        inline void set_delay(MdFloat) noexcept override final;

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
