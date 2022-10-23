#include <vector>
#include "huffman_compressor.h"
#include "plain_compressor.h"

std::vector<Compressor*> compressors = {
    new PlainCompressor(),
    new HuffmanCompressor()
};