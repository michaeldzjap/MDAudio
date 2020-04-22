#ifndef MD_AUDIO_ALLPASS_HPP
#define MD_AUDIO_ALLPASS_HPP

#include "Buffer.hpp"
#include "Processable.hpp"
#include "Reader.hpp"
#include "Writer.hpp"

namespace md_audio {

    class Allpass : public Processable<MdFloat, MdFloat> {
    public:
        explicit Allpass(memory::Allocatable<MdFloat*>&, MdFloat);

        explicit Allpass(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat);

        explicit Allpass(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat, MdFloat);

        void initialise();

        inline void set_delay(MdFloat) noexcept;

        inline void set_gain(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        Buffer m_buffer;
        Reader m_reader;
        Writer m_writer;
        MdFloat m_max_delay;
        std::uint32_t m_delay;
        MdFloat m_gain = 0.;
    };

}

#endif /* MD_AUDIO_ALLPASS_HPP */
