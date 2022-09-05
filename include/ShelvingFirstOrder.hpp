#ifndef MD_AUDIO_SHELVING_FIRST_ORDER_HPP
#define MD_AUDIO_SHELVING_FIRST_ORDER_HPP

namespace md_audio {

    class ShelvingFirstOrder {
    public:
        void set_gain(double gain) noexcept;

    protected:
        double m_m2;
    };

}

#endif /* MD_AUDIO_SHELVING_FIRST_ORDER_HPP */
