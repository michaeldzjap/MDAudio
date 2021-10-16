#include <catch2/catch_test_macros.hpp>
#include "Buffer.hpp"
#include "memory/StaticAllocator.hpp"
#include "memory/StaticPool.hpp"
#include "types.hpp"
#include "Writer.hpp"

using md_audio::Buffer;
using md_audio::MdFloat;
using md_audio::memory::StaticAllocator;
using md_audio::memory::StaticPool;
using md_audio::Writer;

TEST_CASE("writers can write content to a buffer", "[Writer]") {
    constexpr auto SIZE = 1024;
    constexpr auto POOL_SIZE = SIZE * sizeof(MdFloat);

    StaticPool<POOL_SIZE> pool;
    StaticAllocator<MdFloat, StaticPool<POOL_SIZE>> allocator(&pool);
    Buffer<StaticAllocator<MdFloat, StaticPool<POOL_SIZE>>> buffer(allocator, SIZE);

    Writer<StaticAllocator<MdFloat, StaticPool<POOL_SIZE>>> writer(buffer);

    REQUIRE(buffer.initialise());

    for (auto i = 0; i < SIZE; i++) {
        writer.write(i);

        REQUIRE(buffer[i] == static_cast<MdFloat>(i));
    }

    writer.write(999.);

    REQUIRE(buffer[0] == 999.);
}
