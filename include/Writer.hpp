#ifndef MD_AUDIO_WRITER_HPP
#define MD_AUDIO_WRITER_HPP

#include "Allocatable.hpp"
#include "Buffer.hpp"

namespace md_audio {

    class Writer {
    public:
        explicit Writer(memory::Allocatable<MdFloat*>&, std::uint32_t);

        virtual void initialise();

        virtual void write(MdFloat) noexcept final;

        virtual void increment(void) noexcept final;

        virtual ~Writer() = 0;

    protected:
        Buffer m_buffer;
        std::uint32_t m_upper_bound_1;
        std::uint32_t m_write_index = 0;
    };

}

#endif /* MD_AUDIO_WRITER_HPP */
