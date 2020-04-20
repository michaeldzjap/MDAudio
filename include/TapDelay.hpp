#ifndef MD_AUDIO_TAP_DELAY_HPP
#define MD_AUDIO_TAP_DELAY_HPP

#include "Processable.hpp"
#include "Writer.hpp"
#include <array>

namespace md_audio {

    template <std::size_t taps = 1>
    class TapDelay : public Processable<std::array<MdFloat, taps>, MdFloat>, public Writer {
    public:
        explicit TapDelay(memory::Allocatable<MdFloat*>&, MdFloat);

        virtual void set_delay(const std::array<MdFloat, taps>&) noexcept;

        virtual void set_delay(std::size_t, MdFloat) noexcept = 0;

        virtual MdFloat get_max_delay() noexcept = 0;

        virtual constexpr std::size_t get_taps() const noexcept;

        virtual std::array<MdFloat, taps> read() noexcept;

        virtual MdFloat read(std::size_t) noexcept = 0;

        virtual std::array<MdFloat, taps> perform(MdFloat) noexcept override final;

    protected:
        std::array<std::uint32_t, taps> m_delay;
        MdFloat m_max_delay;
    };

    template <std::size_t taps>
    TapDelay<taps>::TapDelay(memory::Allocatable<MdFloat*>& allocator, MdFloat max_delay) :
        Writer(allocator, static_cast<std::uint32_t>(max_delay)),
        m_max_delay(max_delay)
    {}

    template <std::size_t taps>
    void TapDelay<taps>::set_delay(const std::array<MdFloat, taps>& delays) noexcept {
        for (auto i = 0; i < taps; i++)
            set_delay(i, delays[i]);
    }

    template <std::size_t taps>
    constexpr std::size_t TapDelay<taps>::get_taps() const noexcept {
        return taps;
    }

    template <std::size_t taps>
    std::array<MdFloat, taps> TapDelay<taps>::read() noexcept {
        std::array<MdFloat, taps> z{};

        for (auto i = 0; i < taps; i++)
            z[i] = read(i);

        return z;
    }

    template <std::size_t taps>
    std::array<MdFloat, taps> TapDelay<taps>::perform(MdFloat in) noexcept {
        this->write(in);

        auto z = read();

        this->increment(); // Increment the write pointer

        return z;
    }

}

#endif /* MD_AUDIO_TAP_DELAY_HPP */
