#ifndef MD_AUDIO_TAP_DELAY_LINEAR_HPP
#define MD_AUDIO_TAP_DELAY_LINEAR_HPP

#include "Processable.hpp"
#include "ReaderLinear.hpp"
#include "Writer.hpp"
#include "utility.hpp"
#include <array>

namespace md_audio {

    template <std::uint16_t TAPS>
    class TapDelayLinear : public Processable<std::array<MdFloat, TAPS>, MdFloat> {
    public:
        explicit TapDelayLinear(memory::Allocatable<MdFloat*>&, MdFloat);

        explicit TapDelayLinear(memory::Allocatable<MdFloat*>&, MdFloat, const std::array<MdFloat, TAPS>&);

        void initialise();

        void set_delay(const std::array<MdFloat, TAPS>&) noexcept;

        inline void set_delay(std::uint16_t, MdFloat) noexcept;

        std::array<MdFloat, TAPS> perform(MdFloat) noexcept override final;

    private:
        Buffer m_buffer;
        ReaderLinear m_reader;
        Writer m_writer;
        MdFloat m_max_delay;
        std::array<std::uint16_t, TAPS> m_delay;
        std::array<MdFloat, TAPS> m_frac;
    };

    template <std::uint16_t TAPS>
    TapDelayLinear<TAPS>::TapDelayLinear(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay) :
        m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
        m_reader(m_buffer),
        m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
        m_max_delay(max_delay)
    {}

    template <std::uint16_t TAPS>
    TapDelayLinear<TAPS>::TapDelayLinear(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay,
        const std::array<MdFloat, TAPS>& delay) :
        m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
        m_reader(m_buffer),
        m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
        m_max_delay(max_delay)
    {
        set_delay(delay);
    }

    template <std::uint16_t TAPS>
    void TapDelayLinear<TAPS>::initialise() {
        m_buffer.initialise();
    }

    template <std::uint16_t TAPS>
    void TapDelayLinear<TAPS>::set_delay(const std::array<MdFloat, TAPS>& delays) noexcept {
        for (auto i = 0; i < TAPS; i++)
            set_delay(i, delays[i]);
    }

    template <std::uint16_t TAPS>
    void TapDelayLinear<TAPS>::set_delay(std::uint16_t index, MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), m_max_delay);

        m_delay[index] = static_cast<std::uint32_t>(delay);
        m_frac[index] = delay - static_cast<MdFloat>(m_delay[index]);
    }

    template <std::uint16_t TAPS>
    std::array<MdFloat, TAPS> TapDelayLinear<TAPS>::perform(MdFloat in) noexcept {
        m_writer.write(in);

        std::array<MdFloat, TAPS> z{};

        for (auto i = 0; i < TAPS; i++)
            z[i] = m_reader.read(m_writer, m_delay[i], m_frac[i]);

        m_writer.increment();

        return z;
    }

}

#endif /* MD_AUDIO_TAP_DELAY_LINEAR_HPP */
