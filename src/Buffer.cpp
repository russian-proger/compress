#include "Buffer.h"

Buffer:: Buffer():
    _begin(nullptr),
    _seek (nullptr),
    _end  (nullptr) {}

Buffer::~Buffer() {}

char* Buffer::begin() const {
    return this->_begin;
}

char* Buffer::end() const {
    return this->_end;
}

char* Buffer::seek() const {
    return this->_seek;
}

Buffer& Buffer::operator=(Buffer& other) {
    this->_begin = other._begin;
    this->_seek  = other._seek;
    this->_end   = other._end;
}

void Buffer::seekg(std::streamsize off, std::ios::seekdir skd) {
    if (skd == std::ios::beg) {
        this->_seek = this->_begin + off;
    } else if (skd == std::ios::cur) {
        this->_seek += off;
    } else if (skd == std::ios::end) {
        this->_seek = this->_end - off - 1;
    } else {
        throw "Buffer::seekg: unrecognized seekdir";
    }
    if (this->_begin > this->_seek || this->_seek >= this->_end) {
        throw "Buffer::seekg: _seek out of bounds";
    }
}

void Buffer::reset() {
    this->seekg(0, std::ios::beg);
}

std::istream& operator>>(std::istream& in, Buffer& ebuf) {
    if (ebuf._begin != nullptr) {
        delete[] ebuf._begin;
    }

    // Current position in stream
    std::streampos pos  = in.tellg();

    // Remaining count of bits to read
    std::size_t size = static_cast<std::size_t>(getRemainingSize(in));

    ebuf._begin = new char[size];
    ebuf._seek  = ebuf._begin;
    ebuf._end   = ebuf._begin + size;

    in.read(ebuf._begin, size);

    return in;
}

std::ostream& operator<<(std::ostream& out, Buffer& ebuf) {
    if (ebuf._seek != nullptr) {
        out.write(ebuf._seek, (ebuf._end - ebuf._seek));
    }

    return out;
}


Buffer& operator>>(Buffer& ebuf, int& var) {
#ifdef DEBUG
    assert(ebuf._begin <= ebuf._seek && ebuf._seek < ebuf._end);
#endif

    var = *reinterpret_cast<int*>(ebuf._seek);
    ebuf.seekg(sizeof(int), std::ios::cur);
    return ebuf;
}