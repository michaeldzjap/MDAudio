#ifndef MD_AUDIO_TPT_SHELVING_ZPP
#define MD_AUDIO_TPT_SHELVING_ZPP

#include <cmath>

namespace md_audio {

    class TptShelving {
    public:
        virtual ~TptShelving() = 0;

    protected:
        inline auto m2(double gain) noexcept;
    };

    auto TptShelving::m2(double gain) noexcept {
        return std::pow(10., gain / 20.);
    }

}

#endif /* MD_AUDIO_TPT_SHELVING_ZPP */
