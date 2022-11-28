#pragma once

// Scheme of compressed sequence:
// [4x256 bytes] [4 bytes] [N bytes]
//  ^~~~~~~~~~~   ^~~~~~~   ^~~~~~~
//  |             |         |
//  |             |         +- compressed data
//  |             |
//  |             +- size of compressed data
//  |
//  +- count of symbols

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#include "../buffer.h"
#include "../byte.h"
#include "../compressor.h"
#include "../utilities.h"

class Arithmetic2Compressor : public Compressor {
    void Encode() override;
    void Decode() override;
    void PrintInfo() override;
};