#ifndef MD_AUDIO_DELAY_CUBIC_HPP
#define MD_AUDIO_DELAY_CUBIC_HPP

#include "Buffer.hpp"
#include "ReaderCubic.hpp"
#include "SampleRate.hpp"
#include "Writer.hpp"
#include "interfaces/Processable.hpp"
#include "utility.hpp"

namespace md_audio {

    class DelayCubic : public SampleRate, public Processable<MdFloat, MdFloat> {
    public:
        explicit DelayCubic(memory::Poolable&, MdFloat);

        explicit DelayCubic(memory::Poolable&, MdFloat, MdFloat);

        inline void set_delay(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        std::uint32_t m_max_delay;
        std::uint32_t m_delay;
        MdFloat m_frac;
        Buffer m_buffer;
        ReaderCubic m_reader;
        Writer m_writer;
    };

    void DelayCubic::set_delay(MdFloat delay) noexcept {
        delay = utility::clip(
            static_cast<MdFloat>(sample_rate * delay),
            static_cast<MdFloat>(1),
            static_cast<MdFloat>(m_max_delay - 2)
        );

        m_delay = static_cast<std::uint32_t>(delay);
        m_frac = delay - static_cast<MdFloat>(m_delay);
    }

}

#endif /* MD_AUDIO_DELAY_CUBIC_HPP */
