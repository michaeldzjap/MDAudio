#ifndef MD_AUDIO_STATIC_POOL_HPP
#define MD_AUDIO_STATIC_POOL_HPP

#include "Poolable.hpp"
#include "Uncopyable.hpp"
#include <algorithm>
#include <cstdint>

namespace md_audio::memory {

    template <std::size_t TOTAL_SIZE>
    class StaticPool : private util::Uncopyable, public Poolable {
    public:
        explicit StaticPool();

        void* allocate(std::size_t size);

        void deallocate(void* ptr) noexcept;

    private:
        std::int8_t m_buffer[TOTAL_SIZE];
        std::int8_t* m_ptr;
    };

    template <std::size_t TOTAL_SIZE>
    StaticPool<TOTAL_SIZE>::StaticPool() : m_ptr(&m_buffer[0]) {}

    template <std::size_t TOTAL_SIZE>
    void* StaticPool<TOTAL_SIZE>::allocate(std::size_t size) {
        if (m_ptr + size - &m_buffer[0] > TOTAL_SIZE)
            throw std::bad_alloc();

        auto ret = m_ptr;

        m_ptr += size;

        return ret;
    }

    template <std::size_t TOTAL_SIZE>
    void StaticPool<TOTAL_SIZE>::deallocate(void* ptr) noexcept {}

}

#endif /* MD_AUDIO_STATIC_POOL_HPP */
