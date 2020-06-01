#ifndef MD_AUDIO_ALLPASS_STATIC_HPP
#define MD_AUDIO_ALLPASS_STATIC_HPP

#include "Buffer.hpp"
#include "Processable.hpp"
#include "Reader.hpp"
#include "Writer.hpp"
#include "utility.hpp"

namespace md_audio {

    class AllpassStatic : public Processable<MdFloat, MdFloat> {
    public:
        explicit AllpassStatic(memory::Poolable&, std::size_t);

        explicit AllpassStatic(memory::Poolable&, std::size_t, MdFloat);

        explicit AllpassStatic(memory::Poolable&, std::size_t, MdFloat, MdFloat);

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

    void AllpassStatic::set_delay(MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), m_max_delay);

        m_delay = static_cast<std::uint32_t>(delay);
    }

    void AllpassStatic::set_gain(MdFloat gain) noexcept {
        m_gain = utility::clip(gain, static_cast<MdFloat>(0), static_cast<MdFloat>(1));
    }

}

#endif /* MD_AUDIO_ALLPASS_STATIC_HPP */
