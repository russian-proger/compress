cmake_minimum_required(VERSION 3.22.1)

project(compress)

add_executable(compress
    src/utilities.cpp
    src/atomic.cpp
    src/buffer.cpp
    src/bitbuffer.cpp
    src/compressor.cpp
    src/compressors/arithmetic.cpp
    src/compressors/huffman.cpp
    src/compressors/plain.cpp
    src/main.cpp
)

if (CMAKE_BUILD_TYPE)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_definitions(-DDEBUG)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_definitions(-O3)
    endif()
endif()
