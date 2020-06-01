#ifndef MD_AUDIO_BUFFER_HPP
#define MD_AUDIO_BUFFER_HPP

#include "Poolable.hpp"
#include "types.hpp"
#include <cstdint>

namespace md_audio {

    class Buffer {
    public:
        explicit Buffer(memory::Poolable&, std::size_t);

        void initialise();

        MdFloat& operator[] (std::size_t) noexcept;

        const MdFloat& operator[] (std::size_t) const noexcept;

        ~Buffer();

    private:
        memory::Poolable& m_pool;
        MdFloat* m_memory = nullptr;
        const std::size_t m_size;
    };

}

#endif /* MD_AUDIO_BUFFER_HPP */
