#pragma once
#include "../compressor.h"
#include "../buffer.h"

class PlainCompressor : public Compressor {
    Buffer   Compress() override;
    Buffer Decompress() override;
};