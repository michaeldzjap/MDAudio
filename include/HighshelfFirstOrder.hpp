#ifndef MD_AUDIO_HIGHSHELF_FIRST_ORDER_HPP
#define MD_AUDIO_HIGHSHELF_FIRST_ORDER_HPP

#include "TptFilter.hpp"
#include "TptShelving.hpp"

namespace md_audio {

    class HighshelfFirstOrder : public TptFilter, public TptShelving {
    public:
        explicit HighshelfFirstOrder();

        explicit HighshelfFirstOrder(double frequency);

        explicit HighshelfFirstOrder(double frequency, double gain);

        void set_frequency(double frequency) noexcept;

        void set_gain(double gain) noexcept;

        double process(double in) noexcept;

    private:
        double m_h;
        double m_m2;
    };

}

#endif /* MD_AUDIO_HIGHSHELF_FIRST_ORDER_HPP */
