#pragma once

#include <map>
#include <string>
#include <vector>
#include "arithmetic.h"
#include "huffman.h"
#include "plain.h"

std::vector<Compressor*> compressors = {
    new PlainCompressor(),
    new HuffmanCompressor(),
    new ArithmeticCompressor()
};

// @todo
std::map<std::string, Compressor*> mcompressors = {
    { "plain", new PlainCompressor() },
    { "huffman", new HuffmanCompressor() },
    { "arithmetic", new ArithmeticCompressor() }
};

// Arithmetic
// Haffman
// LZ
// RLE
// BRW
// SK