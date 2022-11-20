#include "utilities.h"

using namespace cmp;

bool cmp::Exists(std::string fname) {
    std::ifstream file;
    file.open(fname);
    return (bool)file;
}

bool cmp::GetBit(byte* src, size_t index) {
    return 1&(src[index/8]>>(index%8));
}

void cmp::SetBit(byte* src, size_t index, bool value) {
    if (GetBit(src, index) != value) {
        src[index/8] ^= ((byte)(1<<index%8));
    }
}

uint64_t cmp::ReverseBits(uint64_t v) {
    return
        (v & 0xff00000000000000ull) >> 56 |
        (v & 0x00ff000000000000ull) >> 40 |
        (v & 0x0000ff0000000000ull) >> 24 |
        (v & 0x000000ff00000000ull) >> 8  |
        (v & 0x00000000ff000000ull) << 8  |
        (v & 0x0000000000ff0000ull) << 24 |
        (v & 0x000000000000ff00ull) << 40 |
        (v & 0x00000000000000ffull) << 56 ;
}


std::streamsize cmp::GetRemainingSize(std::istream& stream) {
    std::streampos streampos = stream.tellg();
    stream.seekg(0, std::ios::end);

    std::streamsize ret = (stream.tellg() - streampos);
    stream.seekg(streampos, std::ios::beg);

    return ret;
}