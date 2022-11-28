#pragma once

#include <map>
#include <string>
#include <vector>
#include "arithmetic.h"
#include "arithmetic2.h"
#include "bookstack.h"
#include "bwt.h"
#include "huffman.h"
#include "lz77.h"
#include "plain.h"
#include "rle.h"

std::vector<Compressor*> compressors = {
    new PlainCompressor(),
    new HuffmanCompressor(),
    new Arithmetic2Compressor(),
    new BWTCompressor(),
    new RLECompressor(),
    new BSCompressor(),
    new LZ77Compressor()
};

// @todo
std::map<std::string, Compressor*> mcompressors = {
    { "plain", new PlainCompressor() },
    { "huffman", new HuffmanCompressor() },
    { "arithmetic", new Arithmetic2Compressor() },
    { "bwt", new BWTCompressor() }
};

// + Arithmetic
// + Haffman
// + LZ
// + RLE
// + BRW
// + SK