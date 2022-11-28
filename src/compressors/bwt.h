#pragma once

// Scheme of compressed sequence:
// [4 bytes] [[N bytes] [4 bytes]] x K
//  ^          ^~~~~~~   ^~~~~~~     ^
//  |          |         |           |
//  |          |         |           +- several blocks
//  |          |         |
//  |          |         +- position of initial string
//  |          |
//  |          +- transformed data (max 2^15 bytes)
//  |
//  +- size of source data

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#include "../bitbuffer.h"
#include "../buffer.h"
#include "../byte.h"
#include "../compressor.h"
#include "../utilities.h"

class BWTCompressor : public Compressor {
    void Encode() override;
    void Decode() override;
    void PrintInfo() override;
};