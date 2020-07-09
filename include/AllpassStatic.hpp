#ifndef MD_AUDIO_ALLPASS_STATIC_HPP
#define MD_AUDIO_ALLPASS_STATIC_HPP

#include "Buffer.hpp"
#include "Reader.hpp"
#include "SampleRate.hpp"
#include "Writer.hpp"
#include "interfaces/Processable.hpp"
#include "utility.hpp"

namespace md_audio {

    class AllpassStatic : public SampleRate, public Processable<MdFloat, MdFloat> {
    public:
        explicit AllpassStatic(memory::Poolable&, MdFloat);

        explicit AllpassStatic(memory::Poolable&, MdFloat, MdFloat);

        explicit AllpassStatic(memory::Poolable&, MdFloat, MdFloat, MdFloat);

        inline void set_delay(MdFloat) noexcept;

        inline void set_gain(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        const MdFloat m_max_delay;
        std::uint32_t m_delay;
        MdFloat m_gain = static_cast<MdFloat>(0);
        Buffer m_buffer;
        Reader m_reader;
        Writer m_writer;
    };

    void AllpassStatic::set_delay(MdFloat delay) noexcept {
        delay = utility::clip(
            static_cast<MdFloat>(sample_rate * delay),
            static_cast<MdFloat>(1),
            static_cast<MdFloat>(m_max_delay)
        );

        m_delay = static_cast<std::uint32_t>(delay);
    }

    void AllpassStatic::set_gain(MdFloat gain) noexcept {
        m_gain = utility::clip(gain, static_cast<MdFloat>(0), static_cast<MdFloat>(1));
    }

}

#endif /* MD_AUDIO_ALLPASS_STATIC_HPP */
