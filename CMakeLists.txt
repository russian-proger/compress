cmake_minimum_required(VERSION 3.22.1)

project(compress)

add_executable(compress
    src/utilities.cpp
    src/atomic.cpp
    src/buffer.cpp
    src/bitbuffer.cpp
    src/compressor.cpp
    src/compressors/haffman_compressor.cpp
    src/compressors/plain_compressor.cpp
    src/main.cpp
)

if (CMAKE_BUILD_TYPE)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_definitions(-DDEBUG)
    endif()
endif()