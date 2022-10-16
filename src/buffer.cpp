#include "buffer.h"

Buffer:: Buffer(): seek_(0){}
Buffer::~Buffer(){}

void Buffer::Reserve(size_t size) {
    this->data_.resize(this->GetSize() + size);
}

char* Buffer::At(size_t index) {
    return this->GetPointerBegin() + index;
}

char* Buffer::AtCurrent() {
    return this->At(this->seek_);
}

char* Buffer::GetPointerBegin() {
    return this->data_.data();
}

char* Buffer::GetPointerEnd() {
    return this->GetPointerBegin() + this->GetSize();
}

size_t Buffer::GetSize() const {
    return this->data_.size();
}

size_t Buffer::GetSeek() const {
    return this->seek_;
}

size_t Buffer::GetLeft() const {
    return this->GetSize() - this->GetSeek();
}

void Buffer::Read(char* destination, size_t size) {
#ifdef DEBUG
    printf("Reading from buffer (%ld bytes)\n", size);
#endif
    assert(this->GetSeek() + size <= this->GetSize());
    memcpy(destination, this->AtCurrent(), size);
    this->seek_ += size;
}

void Buffer::Write(char* source, size_t size) {
    this->Reserve(size);
    memcpy(this->GetPointerEnd() - size, source, size);
}

std::istream& operator>>(std::istream& in, Buffer& buffer) {
    // Current position in stream
    std::streampos pos  = in.tellg();

    // Remaining count of bits to read
    std::size_t stream_size = static_cast<std::size_t>(GetRemainingSize(in));

    // Extending of buffer.data & writing from stream
    buffer.Reserve(stream_size);
    in.read(buffer.GetPointerEnd() - stream_size, stream_size);

    return in;
}

std::ostream& operator<<(std::ostream& out, Buffer& buffer) {
    if (buffer.GetSize() > 0) {
        out.write(buffer.AtCurrent(), buffer.GetLeft());
    }

    return out;
}

Buffer& operator>>(Buffer& buffer, Atomic& atomic) {
    buffer.Read(atomic.getData(), atomic.getSize());
    return buffer;
}