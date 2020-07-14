#ifndef MD_AUDIO_ALLPASS_CUBIC_HPP
#define MD_AUDIO_ALLPASS_CUBIC_HPP

#include "Buffer.hpp"
#include "ReaderCubic.hpp"
#include "SampleRate.hpp"
#include "Writer.hpp"
#include "interfaces/Processable.hpp"
#include "utility.hpp"

namespace md_audio {

    class AllpassCubic : public SampleRate, public Processable<MdFloat, MdFloat> {
    public:
        explicit AllpassCubic(memory::Poolable&, MdFloat);

        explicit AllpassCubic(memory::Poolable&, MdFloat, MdFloat);

        explicit AllpassCubic(memory::Poolable&, MdFloat, MdFloat, MdFloat);

        inline void set_delay(MdFloat) noexcept;

        inline void set_gain(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        const std::uint32_t m_max_delay;
        std::uint32_t m_delay;
        MdFloat m_gain = static_cast<MdFloat>(0);
        MdFloat m_frac;
        Buffer m_buffer;
        ReaderCubic m_reader;
        Writer m_writer;
    };

    void AllpassCubic::set_delay(MdFloat delay) noexcept {
        delay = utility::clip(
            static_cast<MdFloat>(m_sample_rate * delay),
            static_cast<MdFloat>(1),
            static_cast<MdFloat>(m_max_delay)
        );

        m_delay = static_cast<std::uint32_t>(delay);
        m_frac = delay - static_cast<MdFloat>(m_delay);
    }

    void AllpassCubic::set_gain(MdFloat gain) noexcept {
        m_gain = utility::clip(gain, static_cast<MdFloat>(0), static_cast<MdFloat>(1));
    }

}

#endif /* MD_AUDIO_ALLPASS_CUBIC_HPP */
