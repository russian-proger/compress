#include "plain_compressor.h"

Buffer PlainCompressor::Compress() {
    return this->buffer_;
}

Buffer PlainCompressor::Decompress() {
    return this->buffer_;
}