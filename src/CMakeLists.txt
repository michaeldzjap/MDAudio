include("${CMAKE_CURRENT_SOURCE_DIR}/sourcelist.cmake")
list(TRANSFORM MD_AUDIO_SOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")

# Only build the object files so that we can reuse them for the test suite
add_library(md_audio OBJECT ${MD_AUDIO_SOURCES})

# Create an executable by simply adding the main entry point
add_executable(mdaudio $<TARGET_OBJECTS:md_audio> "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

if (MSVC)
    target_compile_options(mdaudio PRIVATE /W4 /WX)
else ()
    target_compile_options(mdaudio PRIVATE -Wall -Wextra -pedantic -Werror)
endif ()
