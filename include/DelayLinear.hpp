#ifndef MD_AUDIO_DELAY_LINEAR_HPP
#define MD_AUDIO_DELAY_LINEAR_HPP

#include "Buffer.hpp"
#include "Delayable.hpp"
#include "ReaderLinear.hpp"
#include "Writer.hpp"
#include "utility.hpp"

namespace md_audio {

    class DelayLinear : public Delayable {
    public:
        explicit DelayLinear(memory::Poolable&, std::size_t);

        explicit DelayLinear(memory::Poolable&, std::size_t, MdFloat);

        inline void set_delay(MdFloat) noexcept override final;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        Buffer m_buffer;
        ReaderLinear m_reader;
        Writer m_writer;
        MdFloat m_max_delay;
        std::uint32_t m_delay;
        MdFloat m_frac;
    };

    void DelayLinear::set_delay(MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), m_max_delay);

        m_delay = static_cast<std::uint32_t>(delay);
        m_frac = delay - static_cast<MdFloat>(m_delay);
    }

}

#endif /* MD_AUDIO_DELAY_LINEAR_HPP */
