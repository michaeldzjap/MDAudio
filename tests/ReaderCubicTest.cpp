#include <catch2/catch_test_macros.hpp>
#include "Buffer.hpp"
#include "ReaderCubic.hpp"
#include "memory/StaticAllocator.hpp"
#include "memory/StaticPool.hpp"

using md_audio::Buffer;
using md_audio::ReaderCubic;
using md_audio::memory::StaticAllocator;
using md_audio::memory::StaticPool;

TEST_CASE("cubicly interpolated readers can read the contents of a buffer", "[ReaderCubic]") {
    constexpr auto SIZE = 1024;
    constexpr auto POOL_SIZE = SIZE * sizeof(double);

    StaticPool<POOL_SIZE> pool;
    StaticAllocator<double, StaticPool<POOL_SIZE>> allocator(&pool);
    Buffer<StaticAllocator<double, StaticPool<POOL_SIZE>>> buffer(allocator, SIZE);

    ReaderCubic<StaticAllocator<double, StaticPool<POOL_SIZE>>> reader(buffer);

    REQUIRE(buffer.initialise());

    buffer[0] = 1.;

    REQUIRE(reader.read(0, .0) == 1.);
    REQUIRE(reader.read(1024, .0) == 1.);
    REQUIRE(reader.read(0, .25) == .8671875);
    REQUIRE(reader.read(0, .5) == .5625);
    REQUIRE(reader.read(0, .75) == .2265625);
    REQUIRE(reader.read(0, 1.) == 0.);
}
