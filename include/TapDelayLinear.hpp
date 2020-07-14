#ifndef MD_AUDIO_TAP_DELAY_LINEAR_HPP
#define MD_AUDIO_TAP_DELAY_LINEAR_HPP

#include "Buffer.hpp"
#include "ReaderLinear.hpp"
#include "SampleRate.hpp"
#include "Writer.hpp"
#include "interfaces/MultiOutProcessable.hpp"
#include "utility.hpp"

namespace md_audio {

    class TapDelayLinear : public SampleRate, public MultiOutProcessable<MdFloat, MdFloat> {
    public:
        explicit TapDelayLinear(memory::Poolable&, MdFloat, std::size_t);

        void set_delay(const MdFloat*) noexcept;

        inline void set_delay(std::size_t, MdFloat) noexcept;

        MdFloat* perform(MdFloat, MdFloat*, std::size_t) noexcept override final;

        void write(MdFloat) noexcept;

        MdFloat read(std::size_t) noexcept;

        ~TapDelayLinear();

    private:
        std::uint32_t m_max_delay;
        std::size_t m_taps;
        std::uint32_t* m_delay = nullptr;
        MdFloat* m_frac = nullptr;
        memory::Poolable& m_pool;
        Buffer m_buffer;
        ReaderLinear m_reader;
        Writer m_writer;

        void initialise();
    };

    void TapDelayLinear::set_delay(std::size_t index, MdFloat delay) noexcept {
        delay = utility::clip(
            static_cast<MdFloat>(m_sample_rate * delay),
            static_cast<MdFloat>(1),
            static_cast<MdFloat>(m_max_delay)
        );

        m_delay[index] = static_cast<std::uint32_t>(delay);
        m_frac[index] = delay - static_cast<MdFloat>(m_delay[index]);
    }

}

#endif /* MD_AUDIO_TAP_DELAY_LINEAR_HPP */
