#ifndef MD_AUDIO_CONSTANTS_HPP
#define MD_AUDIO_CONSTANTS_HPP

namespace md_audio {

    constexpr double sample_rate = static_cast<double>(44100);
    constexpr double sample_duration = 1. / sample_rate;
    constexpr double half_sample_rate = sample_rate * .5;

    constexpr double pi = 3.1415926535897931;
    constexpr double two_pi = 6.2831853071795862;
    constexpr double half_pi = 1.5707963267948966;

}

#endif /* MD_AUDIO_CONSTANTS_HPP */
