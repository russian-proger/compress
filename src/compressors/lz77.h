#pragma once

// Scheme of compressed sequence:
// [N bytes]
//  ^~~~~~~
//  + compressed data

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#include "../buffer.h"
#include "../byte.h"
#include "../compressor.h"
#include "../utilities.h"

class LZ77Compressor : public Compressor {
    void Encode() override;
    void Decode() override;
    void PrintInfo() override;
};