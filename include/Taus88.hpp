#ifndef MD_AUDIO_TAUS_88_HPP
#define MD_AUDIO_TAUS_88_HPP

#include <cstdint>

namespace md_audio {

    // Original source: https://github.com/supercollider/supercollider/blob/develop/include/plugin_interface/SC_RGen.h

    class Taus88 {
    public:
        explicit Taus88();

        explicit Taus88(std::int32_t);

        void initialise(std::int32_t) noexcept;

        double generate() noexcept;

    private:
        std::uint32_t m_s1;
        std::uint32_t m_s2;
        std::uint32_t m_s3;

        static constexpr std::int32_t Hash(std::int32_t in_key) noexcept {
            auto hash = static_cast<std::uint32_t>(in_key);

            hash += ~(hash << 15);
            hash ^= hash >> 10;
            hash += hash << 3;
            hash ^= hash >> 6;
            hash += ~(hash << 11);
            hash ^= hash >> 16;

            return static_cast<std::int32_t>(hash);
        }

        std::uint32_t trand(std::uint32_t& s1, std::uint32_t& s2, std::uint32_t& s3) noexcept {
            s1 = ((s1 & static_cast<std::uint32_t>(-2)) << 12) ^ (((s1 << 13) ^ s1) >> 19);
            s2 = ((s2 & static_cast<std::uint32_t>(-8)) << 4) ^ (((s2 << 2) ^ s2) >> 25);
            s3 = ((s3 & static_cast<std::uint32_t>(-16)) << 17) ^ (((s3 << 3) ^ s3) >> 11);

            return s1 ^ s2 ^ s3;
        }
    };

}

#endif /* MD_AUDIO_TAUS_88_HPP */
