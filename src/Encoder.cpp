#include "Encoder.h"

Encoder:: Encoder() {}
Encoder::~Encoder() {}

Encoder::Encoder(EncoderBuffer ebuf)
{
    this->_source = ebuf;
}

void Encoder::setEncoderBuffer(EncoderBuffer ebuf) {
    this->_source = ebuf;
}

EncoderBuffer Encoder::decode() {
    EncoderBuffer ret;
    return ret;
}

EncoderBuffer Encoder::encode() {
    EncoderBuffer ret;
    return ret;
}