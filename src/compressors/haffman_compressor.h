#pragma once
#include "../buffer.h"
#include "../compressor.h"

class HaffmanCompressor : public Compressor {
    Buffer   Compress() override;
    Buffer Decompress() override;
};