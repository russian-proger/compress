#pragma once

// Scheme of compressed sequence:
// [1 byte] [M bytes] [M bytes] [8 bytes] [N bytes]
//  ^        ^         ^         ^         ^
//  |        |         |         |         |
//  |        |         |         |         -- compressed data
//  |        |         |         -- size of compressed data
//  |        |         -- char order
//  |        -- depth of certain symbol in prefix-tree
//  -- count of used symbols (M)

#include <algorithm>
#include <numeric>

#include "../bitbuffer.h"
#include "../buffer.h"
#include "../byte.h"
#include "../compressor.h"

using namespace compress;

class HuffmanCompressor : public Compressor {
    Buffer Encode() override;
    Buffer Decode() override;
};