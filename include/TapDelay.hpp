#ifndef MD_AUDIO_TAP_DELAY_HPP
#define MD_AUDIO_TAP_DELAY_HPP

#include "Buffer.hpp"
#include "InterpolationType.hpp"
#include "Reader.hpp"
#include "ReaderCubic.hpp"
#include "ReaderLinear.hpp"
#include "SampleRate.hpp"
#include "Writer.hpp"
#include "interfaces/MultiOutProcessable.hpp"
#include "utility.hpp"

namespace md_audio {

    class TapDelay : public SampleRate, public MultiOutProcessable<MdFloat, MdFloat> {
    public:
        explicit TapDelay(memory::Poolable&, MdFloat, std::size_t, InterpolationType = InterpolationType::none);

        void set_delay(const MdFloat*) noexcept;

        inline void set_delay(std::size_t, MdFloat) noexcept;

        MdFloat* perform(MdFloat, MdFloat*, std::size_t) noexcept override final;

        void write(MdFloat) noexcept;

        MdFloat read(std::size_t) noexcept;

        ~TapDelay();

    private:
        std::uint32_t m_max_delay;
        std::size_t m_taps;
        std::uint32_t* m_delay = nullptr;
        MdFloat* m_frac = nullptr;
        memory::Poolable& m_pool;
        Buffer m_buffer;
        Reader m_reader;
        ReaderLinear m_reader_linear;
        ReaderCubic m_reader_cubic;
        Writer m_writer;

        void initialise(InterpolationType);

        MdFloat* (TapDelay::*perform_function)(MdFloat, MdFloat*, std::size_t) noexcept;

        MdFloat* perform_static(MdFloat, MdFloat*, std::size_t) noexcept;

        MdFloat* perform_linear(MdFloat, MdFloat*, std::size_t) noexcept;

        MdFloat* perform_cubic(MdFloat, MdFloat*, std::size_t) noexcept;

        MdFloat (TapDelay::*read_function)(std::size_t) noexcept;

        MdFloat read_static(std::size_t) noexcept;

        MdFloat read_linear(std::size_t) noexcept;

        MdFloat read_cubic(std::size_t) noexcept;
    };

    void TapDelay::set_delay(std::size_t index, MdFloat delay) noexcept {
        delay = utility::clip(
            static_cast<MdFloat>(m_sample_rate * delay),
            static_cast<MdFloat>(1),
            static_cast<MdFloat>(m_max_delay)
        );

        m_delay[index] = static_cast<std::uint32_t>(delay);
        m_frac[index] = delay - static_cast<MdFloat>(m_delay[index]);
    }

}

#endif /* MD_AUDIO_TAP_DELAY_HPP */
