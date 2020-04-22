#ifndef MD_AUDIO_DELAY_LINEAR_HPP
#define MD_AUDIO_DELAY_LINEAR_HPP

#include "Buffer.hpp"
#include "Processable.hpp"
#include "Reader.hpp"
#include "Writer.hpp"

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
        Reader m_reader;
        Writer m_writer;
        MdFloat m_max_delay;
        std::uint32_t m_delay;
        MdFloat m_frac;
    };

}

#endif /* MD_AUDIO_DELAY_LINEAR_HPP */
