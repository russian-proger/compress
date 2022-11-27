#pragma once

#include <map>
#include <string>
#include <vector>
#include "arithmetic.h"
#include "arithmetic2.h"
#include "bwt.h"
#include "huffman.h"
#include "plain.h"
#include "rle.h"

std::vector<Compressor*> compressors = {
    new PlainCompressor(),
    new HuffmanCompressor(),
    new Arithmetic2Compressor(),
    new BWTCompressor(),
    new RLECompressor(),
};

// @todo
std::map<std::string, Compressor*> mcompressors = {
    { "plain", new PlainCompressor() },
    { "huffman", new HuffmanCompressor() },
    { "arithmetic", new Arithmetic2Compressor() },
    { "bwt", new BWTCompressor() }
};

// - Arithmetic
// - Haffman
// LZ
// RLE
// - BRW
// * SK