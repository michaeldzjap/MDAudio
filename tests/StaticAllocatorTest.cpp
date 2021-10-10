#include <catch2/catch_test_macros.hpp>
#include "memory/StaticAllocator.hpp"
#include "memory/StaticPool.hpp"

using md_audio::memory::StaticAllocator;
using md_audio::memory::StaticPool;

TEST_CASE("static allocators can allocate and deallocate memory", "[StaticAllocator]") {
    constexpr auto SIZE = 1024;
    constexpr auto POOL_SIZE = SIZE * sizeof(float);

    StaticPool<POOL_SIZE> pool;
    StaticAllocator<float, StaticPool<POOL_SIZE>> allocator(&pool);

    auto block_a = allocator.allocate(SIZE);

    SECTION("memory can be allocated up to the given size") {
        REQUIRE(block_a != nullptr);

        auto block_b = allocator.allocate(1);

        REQUIRE(block_b == nullptr);
    }
    SECTION("memory can be deallocated") {
        REQUIRE_NOTHROW(allocator.deallocate(block_a));
    }
}
