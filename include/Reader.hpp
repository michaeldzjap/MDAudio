#ifndef MD_AUDIO_READER_HPP
#define MD_AUDIO_READER_HPP

#include "Buffer.hpp"
#include "Writer.hpp"
#include "types.hpp"

namespace md_audio {

    class Reader {
    public:
        explicit Reader(Buffer&, Writer&);

        explicit Reader(Buffer&, std::uint32_t);

        explicit Reader(Buffer&, std::uint32_t, std::uint32_t);

        MdFloat read(Writer&, std::uint32_t) noexcept;

    private:
        Buffer& m_buffer;
        std::uint32_t m_lower_bound = 0;
        std::uint32_t m_upper_bound;
    };

}

#endif /* MD_AUDIO_READER_HPP */
