cmake_minimum_required(VERSION 3.22.1)

project(compress)

add_executable(compress
    src/Utilities.cpp
    src/EncoderBuffer.cpp
    src/Encoder.cpp
    src/encoders/HaffmanEncoder.cpp
    src/encoders/PlainEncoder.cpp
    src/main.cpp
)
