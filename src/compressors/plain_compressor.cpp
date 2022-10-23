#include "plain_compressor.h"

Buffer PlainCompressor::Encode() {
    return this->buffer_;
}

Buffer PlainCompressor::Decode() {
    return this->buffer_;
}