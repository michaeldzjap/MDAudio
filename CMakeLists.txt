cmake_minimum_required(VERSION 3.12)
project (MDAudio VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/include/memory")

add_subdirectory(src)

include(CTest)

if (BUILD_TESTING)
    add_subdirectory(vendor/catch2)
    add_subdirectory(tests)
endif()
