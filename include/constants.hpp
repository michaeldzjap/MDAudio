#ifndef MD_AUDIO_CONSTANTS_HPP
#define MD_AUDIO_CONSTANTS_HPP

namespace md_audio {

    constexpr auto sample_rate = static_cast<double>(44100);
    constexpr auto sample_duration = 1. / sample_rate;
    constexpr auto half_sample_rate = sample_rate * .5;

    constexpr auto two_pi = 6.2831853071795862;
    constexpr auto pi = 3.1415926535897931;
    constexpr auto three_quarter_pi = 2.3561944901923448;
    constexpr auto half_pi = 1.5707963267948966;
    constexpr auto quarter_pi = .7853981633974483;

    constexpr auto pi_over_sample_rate = pi * sample_duration;

}

#endif /* MD_AUDIO_CONSTANTS_HPP */
