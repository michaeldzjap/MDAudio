#ifndef MD_AUDIO_DELAY_HPP
#define MD_AUDIO_DELAY_HPP

#include "Buffer.hpp"
#include "Delayable.hpp"
#include "InterpolationType.hpp"
#include "Reader.hpp"
#include "ReaderCubic.hpp"
#include "ReaderLinear.hpp"
#include "Writer.hpp"
#include "utility.hpp"

namespace md_audio {

    class Delay : public Delayable {
    public:
        explicit Delay(memory::Poolable&, std::size_t, InterpolationType = InterpolationType::none);

        explicit Delay(memory::Poolable&, std::size_t, MdFloat, InterpolationType = InterpolationType::none);

        inline void set_delay(MdFloat) noexcept override final;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        Buffer m_buffer;
        Reader m_reader;
        ReaderLinear m_reader_linear;
        ReaderCubic m_reader_cubic;
        Writer m_writer;
        MdFloat m_max_delay;
        std::uint32_t m_delay;
        MdFloat m_frac;

        void initialise(std::size_t, MdFloat, InterpolationType) noexcept;

        MdFloat (Delay::*perform_function)(MdFloat) noexcept;

        MdFloat perform_static(MdFloat) noexcept;

        MdFloat perform_linear(MdFloat) noexcept;

        MdFloat perform_cubic(MdFloat) noexcept;
    };

    void Delay::set_delay(MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), m_max_delay);

        m_delay = static_cast<std::uint32_t>(delay);
        m_frac = delay - static_cast<MdFloat>(m_delay);
    }

}

#endif /* MD_AUDIO_DELAY_HPP */
