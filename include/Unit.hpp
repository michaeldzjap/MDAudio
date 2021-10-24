#ifndef MD_AUDIO_UNIT_HPP
#define MD_AUDIO_UNIT_HPP

namespace md_audio {

    class Unit {
    public:
        static double get_sample_rate() noexcept;

        static void set_sample_rate(double sample_rate) noexcept;

        static double get_sample_duration() noexcept;

    protected:
        static double m_sample_rate;
        static double m_sample_duration;
    };

}

#endif /* MD_AUDIO_UNIT_HPP */
