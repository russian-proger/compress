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

std::streamsize cmp::GetRemainingSize(std::istream& stream) {
    std::streampos streampos = stream.tellg();
    stream.seekg(0, std::ios::end);

    std::streamsize ret = (stream.tellg() - streampos);
    stream.seekg(streampos, std::ios::beg);

    return ret;
}