#include "EncoderBuffer.h"

EncoderBuffer:: EncoderBuffer():
    _begin(nullptr),
    _end  (nullptr) {}

EncoderBuffer::~EncoderBuffer() {}

char* EncoderBuffer::begin() const {
    return this->_begin;
}

char* EncoderBuffer::end() const {
    return this->_end;
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
    ebuf._end   = ebuf._begin + size;

    in.read(ebuf._begin, size);

    return in;
}

std::ostream& operator<<(std::ostream& out, EncoderBuffer& ebuf) {
    if (ebuf._begin != nullptr) {
        out.write(ebuf._begin, (ebuf._end - ebuf._begin));
    }

    return out;
}