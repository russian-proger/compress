#include "compressor.h"

Compressor:: Compressor() {}
Compressor::~Compressor() {}

Compressor::Compressor(Buffer buffer)
{
    this->buffer_ = buffer;
}

void Compressor::SetBuffer(Buffer buffer) {
    this->buffer_ = buffer;
}
Buffer Compressor::GetBuffer() {
    return this->buffer_;
}

Buffer Compressor::Decompress() {
    Buffer ret;
    return ret;
}

Buffer Compressor::Compress() {
    Buffer ret;
    return ret;
}