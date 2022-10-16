#include <vector>
#include "haffman_compressor.h"
#include "plain_compressor.h"

std::vector<Compressor*> compressors = {
    new PlainCompressor(),
    new HaffmanCompressor()
};