#ifndef MD_AUDIO_DELAY_CUBIC_HPP
#define MD_AUDIO_DELAY_CUBIC_HPP

#include "Buffer.hpp"
#include "Delayable.hpp"
#include "ReaderCubic.hpp"
#include "Writer.hpp"
#include "utility.hpp"

namespace md_audio {

    class DelayCubic : public Delayable {
    public:
        explicit DelayCubic(memory::Poolable&, MdFloat);

        explicit DelayCubic(memory::Poolable&, MdFloat, MdFloat);

        void initialise() override final;

        inline void set_delay(MdFloat) noexcept override final;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        Buffer m_buffer;
        ReaderCubic m_reader;
        Writer m_writer;
        MdFloat m_max_delay;
        std::uint32_t m_delay;
        MdFloat m_frac;
    };

    void DelayCubic::set_delay(MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), m_max_delay);

        m_delay = static_cast<std::uint32_t>(delay);
        m_frac = delay - static_cast<MdFloat>(m_delay);
    }

}

#endif /* MD_AUDIO_DELAY_CUBIC_HPP */
