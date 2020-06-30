#ifndef MD_AUDIO_TPT_FILTER_HPP
#define MD_AUDIO_TPT_FILTER_HPP

#include "SampleRate.hpp"
#include "utility.hpp"
#include <cmath>

namespace md_audio {

    class TptFilter : public SampleRate {
    public:
        virtual ~TptFilter() = 0;

    protected:
        inline auto g(const double) noexcept;
    };

    auto TptFilter::g(const double frequency) noexcept {
        return std::tan(utility::clip(frequency, 0., m_half_sample_rate) * m_pi_over_sample_rate);
    }

}

#endif /* MD_AUDIO_TPT_FILTER_HPP */
