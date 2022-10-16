#pragma once
#include "../compressor.h"
#include "../buffer.h"

class HaffmanCompressor : public Compressor {
    Buffer   Compress() override;
    Buffer Decompress() override;
};