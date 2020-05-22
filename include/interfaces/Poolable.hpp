#ifndef MD_AUDIO_POOLABLE_HPP
#define MD_AUDIO_POOLABLE_HPP

#include <cstddef>

namespace md_audio::memory {

    class Poolable {
    public:
        /**
         * Allocate "size" number of bytes.
         *
         * @param  size  The number of bytes to allocate
         * @return       The pointer to the allocated memory block
         */
        virtual void* allocate(std::size_t size) = 0;

        /**
         * Deallocate the given pointer.
         *
         * @param  ptr  The pointer to the memory block to be deallocated
         */
        virtual void deallocate(void* ptr) noexcept = 0;
    };

}

#endif /* MD_AUDIO_POOLABLE_HPP */
