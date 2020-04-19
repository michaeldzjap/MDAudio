#ifndef MD_AUDIO_ALLOCATABLE_HPP
#define MD_AUDIO_ALLOCATABLE_HPP

#include <cstdint>

namespace md_audio::memory {

    template <typename pointer>
    class Allocatable {
    public:
        /**
         * Allocate "n" items of the type pointed to by "pointer".
         *
         * @param  n  The number of items to allocate
         * @return    The pointer to the allocated memory block
         */
        [[nodiscard]] virtual pointer allocate(std::size_t n) = 0;

        /**
         * Deallocate the given pointer.
         *
         * @param  ptr  The pointer to the memory block to be deallocated
         * @param  n    The number of items to deallocate
         */
        virtual void deallocate(pointer ptr, std::size_t n [[maybe_unused]]) = 0;
    };

}

#endif /* MD_AUDIO_ALLOCATABLE_HPP */
