#ifndef MD_AUDIO_BUFFER_HPP
#define MD_AUDIO_BUFFER_HPP

#include "Allocatable.hpp"
#include "types.hpp"
#include <cstdint>

namespace md_audio {

    class Buffer {
    public:
        explicit Buffer(memory::Allocatable<MdFloat*>&, std::uint32_t);

        void initialise();

        MdFloat& operator[] (std::uint32_t) noexcept;

        const MdFloat& operator[] (std::uint32_t) const noexcept;

        ~Buffer();

    private:
        memory::Allocatable<MdFloat*>& m_allocator;
        MdFloat* m_memory = nullptr;
        const std::uint32_t m_size;
    };

}

#endif /* MD_AUDIO_BUFFER_HPP */
