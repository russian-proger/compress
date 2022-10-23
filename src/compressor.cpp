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

Buffer Compressor::Decode() {
    Buffer ret;
    return ret;
}

Buffer Compressor::Encode() {
    Buffer ret;
    return ret;
}