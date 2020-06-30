#ifndef MD_AUDIO_DELAY_HPP
#define MD_AUDIO_DELAY_HPP

#include "Buffer.hpp"
#include "InterpolationType.hpp"
#include "Reader.hpp"
#include "ReaderCubic.hpp"
#include "ReaderLinear.hpp"
#include "SampleRate.hpp"
#include "Writer.hpp"
#include "interfaces/Processable.hpp"
#include "utility.hpp"

namespace md_audio {

    class Delay : public SampleRate, public Processable<MdFloat, MdFloat> {
    public:
        explicit Delay(memory::Poolable&, MdFloat, InterpolationType = InterpolationType::none);

        explicit Delay(memory::Poolable&, MdFloat, MdFloat, InterpolationType = InterpolationType::none);

        inline void set_delay(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        std::uint32_t m_max_delay;
        std::uint32_t m_delay;
        MdFloat m_frac;
        Buffer m_buffer;
        Reader m_reader;
        ReaderLinear m_reader_linear;
        ReaderCubic m_reader_cubic;
        Writer m_writer;

        void initialise(MdFloat, InterpolationType) noexcept;

        MdFloat (Delay::*perform_function)(MdFloat) noexcept;

        MdFloat perform_static(MdFloat) noexcept;

        MdFloat perform_linear(MdFloat) noexcept;

        MdFloat perform_cubic(MdFloat) noexcept;

        std::uint32_t compute_max_delay(MdFloat, InterpolationType) noexcept;
    };

    void Delay::set_delay(MdFloat delay) noexcept {
        delay = utility::clip(
            static_cast<MdFloat>(sample_rate * delay),
            static_cast<MdFloat>(1),
            static_cast<MdFloat>(m_max_delay)
        );

        m_delay = static_cast<std::uint32_t>(delay);
        m_frac = delay - static_cast<MdFloat>(m_delay);
    }

}

#endif /* MD_AUDIO_DELAY_HPP */
