#pragma once

// Scheme of compressed sequence:
// [4x256 bytes] [8 bytes] [N bytes]
//  ^             ^         ^
//  |             |         |
//  |             |         -- compressed data
//  |             -- size of compressed data
//  -- count of symbols

#include <algorithm>
#include <iostream>
#include <numeric>

#include "../bitbuffer.h"
#include "../buffer.h"
#include "../byte.h"
#include "../compressor.h"
#include "../utilities.h"

class HuffmanCompressor : public Compressor {
    void Encode() override;
    void Decode() override;
};