Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

include("${CMAKE_CURRENT_SOURCE_DIR}/sourcelist.cmake")
list(TRANSFORM TESTS_SOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")

# add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/catch2" build)
add_executable(tests $<TARGET_OBJECTS:md_audio> ${TESTS_SOURCES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/vendor/catch2/extras")
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)
