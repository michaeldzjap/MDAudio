#include <catch2/catch_test_macros.hpp>
#include "memory/StaticPool.hpp"

using md_audio::memory::StaticPool;

TEST_CASE("static pools can allocate and deallocate memory", "[StaticPool]") {
    constexpr auto SIZE = 1024 * sizeof(double);

    StaticPool<SIZE> pool;

    auto block_a = pool.allocate(SIZE);

    SECTION("memory can be allocated up to the given size") {
        REQUIRE(block_a != nullptr);

        auto block_b = pool.allocate(1);

        REQUIRE(block_b == nullptr);
    }
    SECTION("memory can be deallocated") {
        REQUIRE_NOTHROW(pool.deallocate(block_a));
    }
}
