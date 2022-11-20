#pragma once

#include <map>
#include <string>
#include <vector>
#include "arithmetic.h"
#include "arithmetic2.h"
#include "bwt.h"
#include "huffman.h"
#include "plain.h"

std::vector<Compressor*> compressors = {
    new PlainCompressor(),
    new HuffmanCompressor(),
    new ArithmeticCompressor(),
    new BWTCompressor(),
    new Arithmetic2Compressor()
};

// @todo
std::map<std::string, Compressor*> mcompressors = {
    { "plain", new PlainCompressor() },
    { "huffman", new HuffmanCompressor() },
    { "arithmetic", new ArithmeticCompressor() },
    { "bwt", new BWTCompressor() },
    { "arithmetic2", new Arithmetic2Compressor() }
};

// Arithmetic
// Haffman
// LZ
// RLE
// BRW
// SK