#ifndef MD_AUDIO_WRITER_HPP
#define MD_AUDIO_WRITER_HPP

#include "Buffer.hpp"
#include "types.hpp"
#include <cstdint>

namespace md_audio {

    class Reader;

    class ReaderCubic;

    class ReaderLinear;

    class Writer {
    public:
        explicit Writer(Buffer&, std::uint32_t);

        explicit Writer(Buffer&, std::uint32_t, std::uint32_t);

        void write(MdFloat) noexcept;

        void increment(void) noexcept;

    private:
        Buffer& m_buffer;
        std::uint32_t m_lower_bound = 0;
        std::uint32_t m_upper_bound;
        std::uint32_t m_write_index = 0;

        friend class Reader;
        friend class ReaderCubic;
        friend class ReaderLinear;
    };

}

#endif /* MD_AUDIO_WRITER_HPP */
