#ifndef MD_AUDIO_TAP_DELAY_STATIC_HPP
#define MD_AUDIO_TAP_DELAY_STATIC_HPP

#include "Buffer.hpp"
#include "Reader.hpp"
#include "SampleRate.hpp"
#include "Writer.hpp"
#include "interfaces/MultiOutProcessable.hpp"
#include "utility.hpp"

namespace md_audio {

    class TapDelayStatic : public SampleRate, public MultiOutProcessable<MdFloat, MdFloat> {
    public:
        explicit TapDelayStatic(memory::Poolable&, MdFloat, std::size_t);

        void set_delay(const MdFloat*) noexcept;

        inline void set_delay(std::size_t, MdFloat) noexcept;

        MdFloat* perform(MdFloat, MdFloat*, std::size_t) noexcept override final;

        void write(MdFloat) noexcept;

        MdFloat read(std::size_t) noexcept;

        ~TapDelayStatic();

    private:
        std::uint32_t m_max_delay;
        std::size_t m_taps;
        std::uint32_t* m_delay = nullptr;
        memory::Poolable& m_pool;
        Buffer m_buffer;
        Reader m_reader;
        Writer m_writer;

        void initialise();
    };

    void TapDelayStatic::set_delay(std::size_t index, MdFloat delay) noexcept {
        delay = utility::clip(
            static_cast<MdFloat>(m_sample_rate * delay),
            static_cast<MdFloat>(1),
            static_cast<MdFloat>(m_max_delay)
        );

        m_delay[index] = static_cast<std::uint32_t>(delay);
    }

}

#endif /* MD_AUDIO_TAP_DELAY_STATIC_HPP */
