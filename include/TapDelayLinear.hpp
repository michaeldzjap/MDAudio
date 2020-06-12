#ifndef MD_AUDIO_TAP_DELAY_LINEAR_HPP
#define MD_AUDIO_TAP_DELAY_LINEAR_HPP

#include "Buffer.hpp"
#include "ReaderLinear.hpp"
#include "Writer.hpp"
#include "interfaces/MultiOutProcessable.hpp"
#include "utility.hpp"

namespace md_audio {

    class TapDelayLinear : public MultiOutProcessable<MdFloat, MdFloat> {
    public:
        explicit TapDelayLinear(memory::Poolable&, std::size_t, std::size_t);

        void set_delay(const MdFloat*) noexcept;

        inline void set_delay(std::size_t, MdFloat) noexcept;

        inline constexpr MdFloat get_max_delay() noexcept;

        MdFloat* perform(MdFloat, MdFloat*, std::size_t) noexcept override final;

        void write(MdFloat) noexcept;

        MdFloat read(std::size_t) noexcept;

        ~TapDelayLinear();

    private:
        memory::Poolable& m_pool;
        Buffer m_buffer;
        ReaderLinear m_reader;
        Writer m_writer;
        MdFloat m_max_delay;
        std::size_t m_taps;
        std::uint32_t* m_delay = nullptr;
        MdFloat* m_frac = nullptr;

        void initialise();

        void* allocate(std::size_t);
    };

    void TapDelayLinear::set_delay(std::size_t index, MdFloat delay) noexcept {
        delay = utility::clip(delay, static_cast<MdFloat>(1), m_max_delay);

        m_delay[index] = static_cast<std::uint32_t>(delay);
        m_frac[index] = delay - static_cast<MdFloat>(m_delay[index]);
    }

    constexpr MdFloat TapDelayLinear::get_max_delay() noexcept {
        return m_max_delay;
    }

}

#endif /* MD_AUDIO_TAP_DELAY_LINEAR_HPP */
