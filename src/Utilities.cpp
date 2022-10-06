#include "Utilities.h"


Data::Data(char *ptr, std::size_t size) {
	this->ptr = ptr;
	this->size = size;
}


bool exists(std::string fname) {
    std::ifstream file;
    file.open(fname);
    return (bool)file;
}

std::streamsize getRemainingSize(std::istream& stream) {
    std::streampos streampos = stream.tellg();
    stream.seekg(0, std::ios::end);

    std::streamsize ret = (stream.tellg() - streampos);
    stream.seekg(streampos, std::ios::beg);

    return ret;
}