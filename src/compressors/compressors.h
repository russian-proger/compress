#pragma once

#include <vector>
#include "huffman.h"
#include "plain.h"

std::vector<Compressor*> compressors = {
    new PlainCompressor(),
    new HuffmanCompressor()
};

// Arithmetic
// Haffman
// LZ
// RLE
// BRW
// SK