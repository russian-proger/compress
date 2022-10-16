#include "utilities.h"

bool Exists(std::string fname) {
    std::ifstream file;
    file.open(fname);
    return (bool)file;
}

std::streamsize GetRemainingSize(std::istream& stream) {
    std::streampos streampos = stream.tellg();
    stream.seekg(0, std::ios::end);

    std::streamsize ret = (stream.tellg() - streampos);
    stream.seekg(streampos, std::ios::beg);

    return ret;
}