#include <catch2/catch_test_macros.hpp>
#include "Buffer.hpp"
#include "memory/StaticAllocator.hpp"
#include "memory/StaticPool.hpp"
#include "ReaderLinear.hpp"
#include "types.hpp"

using md_audio::Buffer;
using md_audio::MdFloat;
using md_audio::ReaderLinear;
using md_audio::memory::StaticAllocator;
using md_audio::memory::StaticPool;

TEST_CASE("linearly interpolated readers can read the contents of a buffer", "[ReaderLinear]") {
    constexpr auto SIZE = 1024;
    constexpr auto POOL_SIZE = SIZE * sizeof(MdFloat);

    StaticPool<POOL_SIZE> pool;
    StaticAllocator<MdFloat, StaticPool<POOL_SIZE>> allocator(&pool);
    Buffer<StaticAllocator<MdFloat, StaticPool<POOL_SIZE>>> buffer(allocator, SIZE);

    ReaderLinear<StaticAllocator<MdFloat, StaticPool<POOL_SIZE>>> reader(buffer);

    REQUIRE(buffer.initialise());

    buffer[0] = 1.;

    REQUIRE(reader.read(0, .0) == 1.);
    REQUIRE(reader.read(1024, .0) == 1.);
    REQUIRE(reader.read(0, .5) == .5);
    REQUIRE(reader.read(1, 1.) == 1.);
}
