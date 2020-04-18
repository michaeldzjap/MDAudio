#ifndef MD_AUDIO_TAP_DELAY_HPP
#define MD_AUDIO_TAP_DELAY_HPP

#include "Processable.hpp"
#include "Writer.hpp"
#include <array>

namespace md_audio {

    template <typename Allocator, std::size_t taps = 1>
    class TapDelay : public Processable<std::array<MdFloat, taps>, MdFloat>, public Writer<Allocator> {
    public:
        explicit TapDelay(Allocator&, MdFloat);

        virtual void set_delay(const std::array<MdFloat, taps>&) noexcept;

        virtual void set_delay(std::size_t, MdFloat) noexcept = 0;

        virtual MdFloat get_max_delay() noexcept = 0;

        virtual std::array<MdFloat, taps> read() noexcept;

        virtual MdFloat read(std::size_t) noexcept = 0;

        virtual std::array<MdFloat, taps> perform(MdFloat) noexcept override final;

    protected:
        std::array<std::uint32_t, taps> m_delay;
        MdFloat m_max_delay;
    };

    template <typename Allocator, std::size_t taps>
    TapDelay<Allocator, taps>::TapDelay(Allocator& allocator, MdFloat max_delay) :
        Writer<Allocator>(allocator, static_cast<std::uint32_t>(max_delay)),
        m_max_delay(max_delay)
    {}

    template <typename Allocator, std::size_t taps>
    void TapDelay<Allocator, taps>::set_delay(const std::array<MdFloat, taps>& delays) noexcept {
        for (auto i = 0; i < taps; i++)
            set_delay(i, delays[i]);
    }

    template <typename Allocator, std::size_t taps>
    std::array<MdFloat, taps> TapDelay<Allocator, taps>::read() noexcept {
        std::array<MdFloat, taps> z{};

        for (auto i = 0; i < taps; i++)
            z[i] = read(i);

        return z;
    }

    template <typename Allocator, std::size_t taps>
    std::array<MdFloat, taps> TapDelay<Allocator, taps>::perform(MdFloat in) noexcept {
        this->write(in);

        auto z = read();

        this->increment(); // Increment the write pointer

        return z;
    }

}

#endif /* MD_AUDIO_TAP_DELAY_HPP */
