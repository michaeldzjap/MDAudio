#ifndef MD_AUDIO_LATCH_HPP
#define MD_AUDIO_LATCH_HPP

namespace md_audio {

    class Latch {
    public:
        double process(double in1, double in2) noexcept;

    private:
        double m_level = 0.;
        double m_previous = 0.;
    };

}

#endif /* MD_AUDIO_LATCH_HPP */
