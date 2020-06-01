#ifndef MD_AUDIO_READER_HPP
#define MD_AUDIO_READER_HPP

#include "Buffer.hpp"
#include "Writer.hpp"
#include "types.hpp"

namespace md_audio {

    class Reader {
    public:
        explicit Reader(Buffer&, Writer&);

        explicit Reader(Buffer&, std::size_t);

        explicit Reader(Buffer&, std::size_t, std::size_t);

        MdFloat read(Writer&, std::size_t) noexcept;

    private:
        Buffer& m_buffer;
        std::size_t m_lower_bound = 0;
        std::size_t m_upper_bound;
    };

}

#endif /* MD_AUDIO_READER_HPP */
