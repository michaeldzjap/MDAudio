#ifndef MD_AUDIO_NORMALISER_HPP
#define MD_AUDIO_NORMALISER_HPP

#include "SampleRate.hpp"
#include "interfaces/Poolable.hpp"
#include "interfaces/Processable.hpp"
#include "types.hpp"
#include "utility.hpp"

namespace md_audio {

    // Original source: https://github.com/supercollider/supercollider/blob/develop/server/plugins/FilterUGens.cpp

    class Normaliser : public SampleRate, public Processable<MdFloat, MdFloat> {
    public:
        explicit Normaliser(memory::Poolable&, MdFloat);

        explicit Normaliser(memory::Poolable&, MdFloat, MdFloat);

        inline void set_amplitude(MdFloat) noexcept;

        MdFloat perform(MdFloat) noexcept override final;

        ~Normaliser();

    private:
        memory::Poolable& m_pool;
        MdFloat* m_memory = nullptr;
        MdFloat* m_in_buf = nullptr;
        MdFloat* m_mid_buf = nullptr;
        MdFloat* m_out_buf = nullptr;
        const std::size_t m_duration;
        const std::size_t m_size;
        MdFloat m_amplitude;
        std::uint32_t m_flips = 0;
        std::uint32_t m_pos = 0;
        MdFloat m_slope = static_cast<MdFloat>(0);
        MdFloat m_level = static_cast<MdFloat>(1);
        MdFloat m_cur_max_val = static_cast<MdFloat>(0);
        MdFloat m_prev_max_val = static_cast<MdFloat>(0);
        MdFloat m_slope_factor;

        void initialise(MdFloat);
    };

    void Normaliser::set_amplitude(MdFloat amplitude) noexcept {
        m_amplitude = utility::clip<MdFloat>(amplitude, 0, 1);
    }

}

#endif /* MD_AUDIO_NORMALISER_HPP */
