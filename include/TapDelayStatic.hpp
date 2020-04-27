#ifndef MD_AUDIO_TAP_DELAY_STATIC_HPP
#define MD_AUDIO_TAP_DELAY_STATIC_HPP

#include "Processable.hpp"
#include "Reader.hpp"
#include "Writer.hpp"
#include "utility.hpp"
#include <array>

namespace md_audio {

    template <std::uint16_t TAPS>
    class TapDelayStatic : public Processable<std::array<MdFloat, TAPS>, MdFloat> {
    public:
        explicit TapDelayStatic(memory::Allocatable<MdFloat*>&, MdFloat);

        explicit TapDelayStatic(memory::Allocatable<MdFloat*>&, MdFloat, const std::array<MdFloat, TAPS>&);

        void initialise();

        void set_delay(const std::array<MdFloat, TAPS>&) noexcept;

        inline void set_delay(std::uint16_t, MdFloat) noexcept;

        inline constexpr MdFloat get_max_delay() noexcept;

        std::array<MdFloat, TAPS> perform(MdFloat) noexcept override final;

        void write(MdFloat) noexcept;

        MdFloat read(std::uint32_t) noexcept;

    private:
        Buffer m_buffer;
        Reader m_reader;
        Writer m_writer;
        MdFloat m_max_delay;
        std::array<std::uint16_t, TAPS> m_delay;
    };

    template <std::uint16_t TAPS>
    TapDelayStatic<TAPS>::TapDelayStatic(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay) :
        m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
        m_reader(m_buffer),
        m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
        m_max_delay(max_delay)
    {}

    template <std::uint16_t TAPS>
    TapDelayStatic<TAPS>::TapDelayStatic(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay,
        const std::array<MdFloat, TAPS>& delay) :
        m_buffer(allocator, static_cast<std::uint32_t>(max_delay)),
        m_reader(m_buffer),
        m_writer(m_buffer, static_cast<std::uint32_t>(max_delay) - 1),
        m_max_delay(max_delay)
    {
        set_delay(delay);
    }

    template <std::uint16_t TAPS>
    void TapDelayStatic<TAPS>::initialise() {
        m_buffer.initialise();
    }

    template <std::uint16_t TAPS>
    void TapDelayStatic<TAPS>::set_delay(const std::array<MdFloat, TAPS>& delays) noexcept {
        for (auto i = 0; i < TAPS; i++)
            set_delay(i, delays[i]);
    }

    template <std::uint16_t TAPS>
    void TapDelayStatic<TAPS>::set_delay(std::uint16_t index, MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), m_max_delay);

        m_delay[index] = static_cast<std::uint32_t>(delay);
    }

    template <std::uint16_t TAPS>
    constexpr MdFloat TapDelayStatic<TAPS>::get_max_delay() noexcept {
        return m_max_delay;
    }

    template <std::uint16_t TAPS>
    std::array<MdFloat, TAPS> TapDelayStatic<TAPS>::perform(MdFloat in) noexcept {
        m_writer.write(in);

        std::array<MdFloat, TAPS> z{};

        for (auto i = 0; i < TAPS; i++)
            z[i] = m_reader.read(m_writer, m_delay[i]);

        m_writer.increment();

        return z;
    }

    template <std::uint16_t TAPS>
    void TapDelayStatic<TAPS>::write(MdFloat in) noexcept {
        m_writer.write(in);

        m_writer.increment();
    }

    template <std::uint16_t TAPS>
    MdFloat TapDelayStatic<TAPS>::read(std::uint32_t index) noexcept {
        return m_reader.read(m_writer, m_delay[index]);
    }

}

#endif /* MD_AUDIO_TAP_DELAY_STATIC_HPP */
