#include <catch2/catch_test_macros.hpp>
#include "Buffer.hpp"
#include "memory/StaticAllocator.hpp"
#include "memory/StaticPool.hpp"
#include "types.hpp"

using md_audio::Buffer;
using md_audio::MdFloat;
using md_audio::memory::StaticAllocator;
using md_audio::memory::StaticPool;

TEST_CASE("buffers can be allocated and initialised", "[Buffer]") {
    constexpr auto SIZE = 1024;
    constexpr auto POOL_SIZE = SIZE * sizeof(MdFloat);

    StaticPool<POOL_SIZE> pool;
    StaticAllocator<MdFloat, StaticPool<POOL_SIZE>> allocator(&pool);

    Buffer<StaticAllocator<MdFloat, StaticPool<POOL_SIZE>>> buffer(allocator, SIZE);

    REQUIRE(buffer.initialise());

    for (auto i = 0; i < SIZE; i++)
        REQUIRE(buffer[i] == .0);
}
