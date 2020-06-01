#ifndef MD_AUDIO_TAP_DELAY_CUBIC_HPP
#define MD_AUDIO_TAP_DELAY_CUBIC_HPP

#include "Buffer.hpp"
#include "ReaderCubic.hpp"
#include "TapDelayable.hpp"
#include "Writer.hpp"
#include "utility.hpp"

namespace md_audio {

    class TapDelayCubic : public TapDelayable {
    public:
        explicit TapDelayCubic(memory::Poolable&, MdFloat, std::size_t);

        void set_delay(const MdFloat*) noexcept override final;

        inline void set_delay(std::size_t, MdFloat) noexcept override final;

        inline constexpr MdFloat get_max_delay() noexcept override final;

        MdFloat* perform(MdFloat, MdFloat*, std::size_t) noexcept override final;

        void write(MdFloat) noexcept override final;

        MdFloat read(std::size_t) noexcept override final;

        ~TapDelayCubic();

    private:
        memory::Poolable& m_pool;
        Buffer m_buffer;
        ReaderCubic m_reader;
        Writer m_writer;
        MdFloat m_max_delay;
        std::size_t m_taps;
        std::uint32_t* m_delay = nullptr;
        MdFloat* m_frac = nullptr;

        void initialise();

        void* allocate(std::size_t);
    };

    void TapDelayCubic::set_delay(std::size_t index, MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), m_max_delay);

        m_delay[index] = static_cast<std::uint32_t>(delay);
        m_frac[index] = delay - static_cast<MdFloat>(m_delay[index]);
    }

    constexpr MdFloat TapDelayCubic::get_max_delay() noexcept {
        return m_max_delay;
    }

}

#endif /* MD_AUDIO_TAP_DELAY_CUBIC_HPP */
