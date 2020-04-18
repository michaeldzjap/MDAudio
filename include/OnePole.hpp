#ifndef MD_AUDIO_ONE_POLE_HPP
#define MD_AUDIO_ONE_POLE_HPP

namespace md_audio {

    class OnePole {
    public:
        virtual ~OnePole() = 0;

    protected:
        double m_s = 0.;
    };

}

#endif /* MD_AUDIO_ONE_POLE_HPP */
