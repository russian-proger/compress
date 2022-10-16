#include "Compressor.h"

Compressor:: Compressor() {}
Compressor::~Compressor() {}

Compressor::Compressor(Buffer buffer)
{
    this->_buffer = buffer;
}

void Compressor::setBuffer(Buffer buffer) {
    this->_buffer = buffer;
}
Buffer Compressor::getBuffer() {
    return this->_buffer;
}

Buffer Compressor::decompress() {
    Buffer ret;
    return ret;
}

Buffer Compressor::compress() {
    Buffer ret;
    return ret;
}