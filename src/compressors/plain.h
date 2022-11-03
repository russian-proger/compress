#pragma once
#include "../byte.h"
#include "../buffer.h"
#include "../compressor.h"

class PlainCompressor : public Compressor {
    void Encode() override;
    void Decode() override;
};