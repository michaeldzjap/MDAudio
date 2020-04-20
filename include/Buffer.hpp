#ifndef MD_AUDIO_BUFFER_HPP
#define MD_AUDIO_BUFFER_HPP

#include "Allocatable.hpp"
#include "types.hpp"
#include "utility.hpp"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <new>

namespace md_audio {

    class Buffer {
    public:
        explicit Buffer(memory::Allocatable<MdFloat*>&, std::uint32_t);

        void initialise();

        MdFloat& operator[] (std::size_t) noexcept;

        const MdFloat& operator[] (std::size_t) const noexcept;

        ~Buffer();

    protected:
        MdFloat* m_memory = nullptr;
        const std::uint32_t m_size;

    private:
        memory::Allocatable<MdFloat*>& m_allocator;
    };

}

#endif /* MD_AUDIO_BUFFER_HPP */
