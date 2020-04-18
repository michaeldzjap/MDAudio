#ifndef MD_AUDIO_DELAY_HPP
#define MD_AUDIO_DELAY_HPP

#include "Processable.hpp"
#include "Writer.hpp"

namespace md_audio {

    template <typename Allocator>
    class Delay : public Processable<MdFloat, MdFloat>, public Writer<Allocator> {
    public:
        explicit Delay(Allocator&, MdFloat);

        virtual void set_delay(MdFloat) noexcept = 0;

        virtual MdFloat get_max_delay() noexcept = 0;

        MdFloat perform(MdFloat) noexcept override final;

        virtual MdFloat read(void) noexcept = 0;

    protected:
        std::uint32_t m_delay;
        MdFloat m_max_delay;
    };

    template <typename Allocator>
    Delay<Allocator>::Delay(Allocator& allocator, MdFloat max_delay) :
        Writer<Allocator>(allocator, static_cast<std::uint32_t>(max_delay)),
        m_max_delay(max_delay)
    {}

    template <typename Allocator>
    MdFloat Delay<Allocator>::perform(MdFloat in) noexcept {
        this->write(in);

        auto z = read();

        this->increment(); // Increment the write pointer

        return z;
    }

}

#endif /* MD_AUDIO_DELAY_HPP */
