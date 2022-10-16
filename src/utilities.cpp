#include "utilities.h"

bool Exists(std::string fname) {
    std::ifstream file;
    file.open(fname);
    return (bool)file;
}

inline bool GetBit(char* src, size_t index) {
    return src[index/8]>>(index%8);
}

inline void SetBit(char* src, size_t index, bool value) {
    if (GetBit(src, index) != value) {
        src[index/8] ^= ((char)(1<<index%8));
    }
}

std::streamsize GetRemainingSize(std::istream& stream) {
    std::streampos streampos = stream.tellg();
    stream.seekg(0, std::ios::end);

    std::streamsize ret = (stream.tellg() - streampos);
    stream.seekg(streampos, std::ios::beg);

    return ret;
}