#ifndef MD_AUDIO_LOWSHELF_FIRST_ORDER_HPP
#define MD_AUDIO_LOWSHELF_FIRST_ORDER_HPP

#include "TptFilter.hpp"
#include "TptShelving.hpp"

namespace md_audio {

    class LowshelfFirstOrder : public TptFilter, public TptShelving {
    public:
        explicit LowshelfFirstOrder();

        explicit LowshelfFirstOrder(double frequency);

        explicit LowshelfFirstOrder(double frequency, double gain);

        void set_frequency(double frequency) noexcept;

        void set_gain(double gain) noexcept;

        double process(double in) noexcept;

    private:
        double m_h;
        double m_m2i;
    };

}

#endif /* MD_AUDIO_LOWSHELF_FIRST_ORDER_HPP */
