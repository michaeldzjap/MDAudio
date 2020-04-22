#ifndef MD_AUDIO_DELAY_CUBIC_HPP
#define MD_AUDIO_DELAY_CUBIC_HPP

#include "Buffer.hpp"
#include "Processable.hpp"
#include "ReaderCubic.hpp"
#include "Writer.hpp"

namespace md_audio {

    class DelayCubic : public Processable<MdFloat, MdFloat> {
    public:
        explicit DelayCubic(memory::Allocatable<MdFloat*>&, MdFloat);

        explicit DelayCubic(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat);

        void initialise();

        inline void set_delay(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        Buffer m_buffer;
        ReaderCubic m_reader;
        Writer m_writer;
        MdFloat m_max_delay;
        std::uint32_t m_delay;
        MdFloat m_frac;
    };

}

#endif /* MD_AUDIO_DELAY_CUBIC_HPP */
