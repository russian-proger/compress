#pragma once
#include "../byte.h"
#include "../buffer.h"
#include "../compressor.h"

using namespace compress;

class PlainCompressor : public Compressor {
    Buffer Encode() override;
    Buffer Decode() override;
};