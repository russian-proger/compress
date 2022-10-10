cmake_minimum_required(VERSION 3.22.1)

project(compress)

add_executable(compress
    src/Utilities.cpp
    src/Buffer.cpp
    src/Compressor.cpp
    src/compressors/HaffmanCompressor.cpp
    src/compressors/PlainCompressor.cpp
    src/main.cpp
)

if (CMAKE_BUILD_TYPE)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_definitions(-DDEBUG)
    endif()
endif()