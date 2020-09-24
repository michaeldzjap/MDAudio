#ifndef MD_AUDIO_ALLPASS_LINEAR_HPP
#define MD_AUDIO_ALLPASS_LINEAR_HPP

#include "Buffer.hpp"
#include "ReaderLinear.hpp"
#include "SampleRate.hpp"
#include "Writer.hpp"
#include "interfaces/Processable.hpp"
#include "utility.hpp"

namespace md_audio {

    class AllpassLinear : public SampleRate, public Processable<MdFloat, MdFloat> {
    public:
        explicit AllpassLinear(memory::Poolable&, MdFloat);

        explicit AllpassLinear(memory::Poolable&, MdFloat, MdFloat);

        explicit AllpassLinear(memory::Poolable&, MdFloat, MdFloat, MdFloat);

        inline void set_delay(MdFloat) noexcept;

        inline void set_gain(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        const std::uint32_t m_max_delay;
        std::uint32_t m_delay;
        MdFloat m_gain = static_cast<MdFloat>(0);
        MdFloat m_frac;
        Buffer m_buffer;
        ReaderLinear m_reader;
        Writer m_writer;
    };

    void AllpassLinear::set_delay(MdFloat delay) noexcept {
        delay = utility::clip<MdFloat>(m_sample_rate * delay, 1, m_max_delay);

        m_delay = static_cast<std::uint32_t>(delay);
        m_frac = delay - static_cast<MdFloat>(m_delay);
    }

    void AllpassLinear::set_gain(MdFloat gain) noexcept {
        m_gain = utility::clip<MdFloat>(gain, 0, 1);
    }

}

#endif /* MD_AUDIO_ALLPASS_LINEAR_HPP */
