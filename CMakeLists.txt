cmake_minimum_required(VERSION 3.12)
project (MDAudio VERSION 0.0.1 LANGUAGES CXX)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    include_directories("${CMAKE_SOURCE_DIR}/include")
    include_directories("${CMAKE_SOURCE_DIR}/include/interfaces")
    include_directories("${CMAKE_SOURCE_DIR}/include/memory")

    add_subdirectory(src)
endif()
