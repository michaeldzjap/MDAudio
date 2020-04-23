#ifndef MD_AUDIO_STATIC_ALLOCATOR_HPP
#define MD_AUDIO_STATIC_ALLOCATOR_HPP

#include "Allocatable.hpp"
#include <type_traits>

namespace md_audio::memory {

    template <typename T, typename Pool>
    class StaticAllocator : public Allocatable<T*> {
    public:
        template <typename U, typename P>
        friend class StaticAllocator;

        using value_type = T;
        using pointer = T*;

        using propagate_on_container_copy_assignment = std::true_type;
        using propagate_on_container_move_assignment = std::true_type;
        using propagate_on_container_swap = std::true_type;

        explicit StaticAllocator(Pool* pool) : m_pool(pool) {}

        template <typename U, typename P>
        StaticAllocator(StaticAllocator<U, P> const& that) : m_pool(that.m_pool) {}

        [[nodiscard]] pointer allocate(std::size_t n) override final {
            return static_cast<pointer>(m_pool->allocate(n * sizeof(T)));
        }

        void deallocate(pointer ptr, std::size_t n [[maybe_unused]]) override final {
            m_pool->deallocate(ptr);
        }

        template <typename U, typename P>
        bool operator==(StaticAllocator<U, P> const& that) const {
            return m_pool == that.m_pool;
        }

        template <typename U, typename P>
        bool operator!=(StaticAllocator<U, P> const& that) const {
            return m_pool != that.m_pool;
        }

    private:
        Pool* m_pool;
    };

}

#endif /* MD_AUDIO_STATIC_ALLOCATOR_HPP */
