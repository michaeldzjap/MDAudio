#ifndef MD_AUDIO_DELAY_LINEAR_HPP
#define MD_AUDIO_DELAY_LINEAR_HPP

#include "Buffer.hpp"
#include "ReaderLinear.hpp"
#include "SampleRate.hpp"
#include "Writer.hpp"
#include "interfaces/Processable.hpp"
#include "utility.hpp"

namespace md_audio {

    class DelayLinear : public SampleRate, public Processable<MdFloat, MdFloat> {
    public:
        explicit DelayLinear(memory::Poolable&, MdFloat);

        explicit DelayLinear(memory::Poolable&, MdFloat, MdFloat);

        inline void set_delay(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        std::uint32_t m_max_delay;
        std::uint32_t m_delay;
        MdFloat m_frac;
        Buffer m_buffer;
        ReaderLinear m_reader;
        Writer m_writer;
    };

    void DelayLinear::set_delay(MdFloat delay) noexcept {
        delay = utility::clip(
            static_cast<MdFloat>(sample_rate * delay),
            static_cast<MdFloat>(1),
            static_cast<MdFloat>(m_max_delay)
        );

        m_delay = static_cast<std::uint32_t>(delay);
        m_frac = delay - static_cast<MdFloat>(m_delay);
    }

}

#endif /* MD_AUDIO_DELAY_LINEAR_HPP */
