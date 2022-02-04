#ifndef MD_AUDIO_SHELVING_SECOND_ORDER_HPP
#define MD_AUDIO_SHELVING_SECOND_ORDER_HPP

namespace md_audio {

    class ShelvingSecondOrder {
    public:
        void set_gain(double gain) noexcept;

    protected:
        double m_m2;
        double m_m4;
    };

}

#endif /* MD_AUDIO_SHELVING_SECOND_ORDER_HPP */
