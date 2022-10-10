#include <vector>
#include "HaffmanCompressor.h"
#include "PlainCompressor.h"

std::vector<Compressor*> compressors = {
    new PlainCompressor(),
    new HaffmanCompressor()
};