#pragma once

// Scheme of compressed code:
// [{u_char} {k * u_char} {k * u_char} {1 * size_t} {content}]
// 
// 0) used symbols count
// 1) each of first (256) bytes contains height of making tree from 0 to 1
// 2) symbols order [posx]
// 3) size of compressed data in bits
// 4) compressed data: making with bitbuffer

#include <algorithm>
#include <numeric>

#include "../bitbuffer.h"
#include "../buffer.h"
#include "../compressor.h"

class HaffmanCompressor : public Compressor {
    Buffer   Compress() override;
    Buffer Decompress() override;
};