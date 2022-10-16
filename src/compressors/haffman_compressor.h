#pragma once

// Scheme of compressed code:
// [{256 * char} {1 * size_t} {content}]
// 
// 1) each of first (256) bytes contains height of making tree from 0 to 1
// 2) size of compressed data in bits
// 3) compressed data: making with bitbuffer


#include "../bitbuffer.h"
#include "../buffer.h"
#include "../compressor.h"

class HaffmanCompressor : public Compressor {
    Buffer   Compress() override;
    Buffer Decompress() override;
};