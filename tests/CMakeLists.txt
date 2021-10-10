include("${CMAKE_CURRENT_SOURCE_DIR}/sourcelist.cmake")
list(TRANSFORM TESTS_SOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")

add_executable(tests $<TARGET_OBJECTS:md_audio> ${TESTS_SOURCES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include_directories("${CMAKE_SOURCE_DIR}/vendor/fakeit/single_header/catch")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/vendor/catch2/extras")
include(Catch)

catch_discover_tests(tests)
