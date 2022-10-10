#pragma once
#include "../Compressor.h"
#include "../Buffer.h"

class HaffmanCompressor : public Compressor {
    Buffer   compress() override;
    Buffer decompress() override;
};