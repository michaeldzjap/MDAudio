#ifndef MD_AUDIO_DELAY_LINEAR_HPP
#define MD_AUDIO_DELAY_LINEAR_HPP

#include "Buffer.hpp"
#include "Processable.hpp"
#include "ReaderLinear.hpp"
#include "Writer.hpp"
#include "utility.hpp"

namespace md_audio {

    class DelayLinear : public Processable<MdFloat, MdFloat> {
    public:
        explicit DelayLinear(memory::Allocatable<MdFloat*>&, MdFloat);

        explicit DelayLinear(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat);

        void initialise();

        inline void set_delay(MdFloat) noexcept;

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
