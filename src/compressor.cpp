#include "compressor.h"

Compressor:: Compressor() {
    this->source_ = nullptr;
    this->buffer_ = nullptr;
    this->output_ = nullptr;
}
Compressor::~Compressor() {}

void Compressor::Decode() {}
void Compressor::Encode() {}

Buffer* Compressor::GetSource() {
    return this->source_;
}
Buffer* Compressor::GetBuffer() {
    return this->buffer_;
}
Buffer* Compressor::GetOutput() {
    return this->output_;
}

void Compressor::SetSource(Buffer *buffer) {
    this->source_ = buffer;
}
void Compressor::SetBuffer(Buffer *buffer) {
    this->buffer_ = buffer;
}
void Compressor::SetOutput(Buffer *buffer) {
    this->output_ = buffer;
}

void Compressor::SetSource(Buffer &buffer) {
    this->source_ = &buffer;
}
void Compressor::SetBuffer(Buffer &buffer) {
    this->buffer_ = &buffer;
}
void Compressor::SetOutput(Buffer &buffer) {
    this->output_ = &buffer;
}