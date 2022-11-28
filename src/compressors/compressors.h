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
    new BSCompressor(),
    new RLECompressor(),
    new LZ77Compressor()
};

// + Arithmetic
// + Haffman
// + LZ
// + RLE
// + BRW
// + SK