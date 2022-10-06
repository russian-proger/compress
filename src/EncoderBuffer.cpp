#include "EncoderBuffer.h"

EncoderBuffer:: EncoderBuffer():
    _begin(nullptr),
    _seek (nullptr),
    _end  (nullptr) {}

EncoderBuffer::~EncoderBuffer() {}

char* EncoderBuffer::begin() const {
    return this->_begin;
}

char* EncoderBuffer::end() const {
    return this->_end;
}

char* EncoderBuffer::seek() const {
    return this->_seek;
}


void EncoderBuffer::seekg(std::streamsize off, std::ios::seekdir skd) {
    if (skd == std::ios::beg) {
        this->_seek = this->_begin + off;
    } else if (skd == std::ios::cur) {
        this->_seek += off;
    } else if (skd == std::ios::end) {
        this->_seek = this->_end - off - 1;
    } else {
        throw "EncoderBuffer::seekg: unrecognized seekdir";
    }
    if (this->_begin > this->_seek || this->_seek >= this->_end) {
        throw "EncoderBuffer::seekg: _seek out of bounds";
    }
}

void EncoderBuffer::reset() {
    this->seekg(0, std::ios::beg);
}

std::istream& operator>>(std::istream& in, EncoderBuffer& ebuf) {
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

std::ostream& operator<<(std::ostream& out, EncoderBuffer& ebuf) {
    if (ebuf._seek != nullptr) {
        out.write(ebuf._seek, (ebuf._end - ebuf._seek));
    }

    return out;
}


EncoderBuffer& operator>>(EncoderBuffer& ebuf, int& var) {
    // if (ebuf._seek + sizeof(int) >= ebuf._end) {
    //     throw "Error while scanning EncoderBuffer";
    // }

    var = *reinterpret_cast<int*>(ebuf._seek);
    ebuf.seekg(sizeof(int), std::ios::cur);
    return ebuf;
}