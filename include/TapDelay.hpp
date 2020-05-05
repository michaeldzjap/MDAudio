#ifndef MD_AUDIO_TAP_DELAY_HPP
#define MD_AUDIO_TAP_DELAY_HPP

#include "Buffer.hpp"
#include "InterpolationType.hpp"
#include "Reader.hpp"
#include "ReaderCubic.hpp"
#include "ReaderLinear.hpp"
#include "TapDelayable.hpp"
#include "Writer.hpp"
#include "utility.hpp"

namespace md_audio {

    class TapDelay : public TapDelayable {
    public:
        explicit TapDelay(memory::Allocatable<MdFloat*>&, MdFloat, std::size_t, InterpolationType = InterpolationType::none);

        explicit TapDelay(memory::Allocatable<MdFloat*>&, MdFloat, const MdFloat*, std::size_t, InterpolationType = InterpolationType::none);

        void initialise() override final;

        void set_delay(const MdFloat*) noexcept override final;

        inline void set_delay(std::size_t, MdFloat) noexcept override final;

        inline constexpr MdFloat get_max_delay() noexcept override final;

        MdFloat* perform(MdFloat, MdFloat*, std::size_t) noexcept override final;

        void write(MdFloat) noexcept override final;

        MdFloat read(std::size_t) noexcept override final;

        ~TapDelay();

    private:
        Buffer m_buffer;
        Reader m_reader;
        ReaderLinear m_reader_linear;
        ReaderCubic m_reader_cubic;
        Writer m_writer;
        MdFloat m_max_delay;
        std::size_t m_taps;
        std::uint32_t* m_delay;
        MdFloat* m_frac;

        void initialise(const MdFloat*, InterpolationType) noexcept;

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
        delay = utility::clip(delay, static_cast<MdFloat>(1), m_max_delay);

        m_delay[index] = static_cast<std::uint32_t>(delay);
        m_frac[index] = delay - static_cast<MdFloat>(m_delay[index]);
    }

    constexpr MdFloat TapDelay::get_max_delay() noexcept {
        return m_max_delay;
    }

}

#endif /* MD_AUDIO_TAP_DELAY_HPP */