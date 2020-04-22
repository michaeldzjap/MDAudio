#ifndef MD_AUDIO_READER_HPP
#define MD_AUDIO_READER_HPP

#include "Buffer.hpp"
#include "Writer.hpp"
#include "types.hpp"

namespace md_audio {

    class Reader {
    public:
        explicit Reader(Buffer&);

        MdFloat read(Writer&, std::uint32_t) noexcept;

    private:
        Buffer& m_buffer;
    };

}

#endif /* MD_AUDIO_READER_HPP */
