#ifndef MD_AUDIO_DELAY_HPP
#define MD_AUDIO_DELAY_HPP

#include "Allocatable.hpp"
#include "Processable.hpp"
#include "Writer.hpp"

namespace md_audio {

    class Delay : public Processable<MdFloat, MdFloat>, public Writer {
    public:
        explicit Delay(memory::Allocatable<MdFloat*>&, MdFloat);

        virtual void set_delay(MdFloat) noexcept = 0;

        virtual MdFloat get_max_delay() noexcept = 0;

        MdFloat perform(MdFloat) noexcept override final;

        virtual MdFloat read(void) noexcept = 0;

    protected:
        std::uint32_t m_delay;
        MdFloat m_max_delay;
    };

}

#endif /* MD_AUDIO_DELAY_HPP */
