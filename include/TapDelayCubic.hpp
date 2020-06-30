#ifndef MD_AUDIO_TAP_DELAY_CUBIC_HPP
#define MD_AUDIO_TAP_DELAY_CUBIC_HPP

#include "Buffer.hpp"
#include "ReaderCubic.hpp"
#include "SampleRate.hpp"
#include "Writer.hpp"
#include "interfaces/MultiOutProcessable.hpp"
#include "utility.hpp"

namespace md_audio {

    class TapDelayCubic : public SampleRate, public MultiOutProcessable<MdFloat, MdFloat> {
    public:
        explicit TapDelayCubic(memory::Poolable&, MdFloat, std::size_t);

        void set_delay(const MdFloat*) noexcept;

        inline void set_delay(std::size_t, MdFloat) noexcept;

        inline constexpr auto get_max_delay() const noexcept;

        MdFloat* perform(MdFloat, MdFloat*, std::size_t) noexcept override final;

        void write(MdFloat) noexcept;

        MdFloat read(std::size_t) noexcept;

        ~TapDelayCubic();

    private:
        std::uint32_t m_max_delay;
        std::size_t m_taps;
        std::uint32_t* m_delay = nullptr;
        MdFloat* m_frac = nullptr;
        memory::Poolable& m_pool;
        Buffer m_buffer;
        ReaderCubic m_reader;
        Writer m_writer;

        void initialise();

        void* allocate(std::size_t);
    };

    void TapDelayCubic::set_delay(std::size_t index, MdFloat delay) noexcept {
        delay = utility::clip(
            static_cast<MdFloat>(sample_rate * delay),
            static_cast<MdFloat>(1),
            static_cast<MdFloat>(m_max_delay)
        );

        m_delay[index] = static_cast<std::uint32_t>(delay);
        m_frac[index] = delay - static_cast<MdFloat>(m_delay[index]);
    }

    constexpr auto TapDelayCubic::get_max_delay() const noexcept {
        return m_max_delay;
    }

}

#endif /* MD_AUDIO_TAP_DELAY_CUBIC_HPP */
