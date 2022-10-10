#pragma once
#include "../Compressor.h"
#include "../Buffer.h"

class PlainCompressor : public Compressor {
    Buffer   compress() override;
    Buffer decompress() override;
};