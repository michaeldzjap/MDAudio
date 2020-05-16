#ifndef MD_AUDIO_NORMALISER_HPP
#define MD_AUDIO_NORMALISER_HPP

#include "Buffer.hpp"
#include "Processable.hpp"
#include "Reader.hpp"
#include "Writer.hpp"
#include "types.hpp"
#include "utility.hpp"

namespace md_audio {

    class Normaliser : public Processable<MdFloat, MdFloat> {
    public:
        explicit Normaliser(memory::Allocatable<MdFloat*>&, std::uint32_t);

        explicit Normaliser(memory::Allocatable<MdFloat*>&, std::uint32_t, MdFloat);

        inline void set_amplitude(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

    private:
        Buffer m_buffer;
        Reader m_reader_in;
        Reader m_reader_mid;
        Reader m_reader_out;
        Writer m_writer;
        MdFloat m_amplitude;
        std::uint32_t m_flips = 0;
        std::uint32_t m_pos = 0;
        MdFloat m_slope = static_cast<MdFloat>(0);
        MdFloat m_level = static_cast<MdFloat>(1);
        MdFloat m_cur_max_val = static_cast<MdFloat>(0);
        MdFloat m_pre_max_val = static_cast<MdFloat>(0);
        MdFloat m_slope_factor;
    };

    void Normaliser::set_amplitude(MdFloat amplitude) noexcept {
        m_amplitude = utility::clip(amplitude, static_cast<MdFloat>(0), static_cast<MdFloat>(1));
    }

}

#endif /* MD_AUDIO_NORMALISER_HPP */
