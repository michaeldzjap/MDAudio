#ifndef MD_AUDIO_ALLPASS_LINEAR_HPP
#define MD_AUDIO_ALLPASS_LINEAR_HPP

#include "Buffer.hpp"
#include "Processable.hpp"
#include "ReaderLinear.hpp"
#include "Writer.hpp"

namespace md_audio {

    class AllpassLinear : public Processable<MdFloat, MdFloat> {
    public:
        explicit AllpassLinear(memory::Allocatable<MdFloat*>&, MdFloat);

        explicit AllpassLinear(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat);

        explicit AllpassLinear(memory::Allocatable<MdFloat*>&, MdFloat, MdFloat, MdFloat);

        void initialise();

        inline void set_delay(MdFloat) noexcept;

        inline void set_gain(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        Buffer m_buffer;
        ReaderLinear m_reader;
        Writer m_writer;
        MdFloat m_max_delay;
        std::uint32_t m_delay;
        MdFloat m_gain = 0.;
        MdFloat m_frac;
    };

}

#endif /* MD_AUDIO_ALLPASS_LINEAR_HPP */
