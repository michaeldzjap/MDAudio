#ifndef MD_AUDIO_READER_LINEAR_HPP
#define MD_AUDIO_READER_LINEAR_HPP

#include "Buffer.hpp"
#include "Writer.hpp"
#include "types.hpp"

namespace md_audio {

    class ReaderLinear {
    public:
        explicit ReaderLinear(Buffer&);

        MdFloat read(Writer&, std::uint32_t, MdFloat) noexcept;

    private:
        Buffer& m_buffer;
    };

}

#endif /* MD_AUDIO_READER_LINEAR_HPP */
