#include "buffer.h"

using namespace cmp;

Buffer:: Buffer(): seek_(0){}
Buffer::~Buffer(){}

Buffer Buffer::Clone() {
    Buffer buffer;
    buffer.seek_ = this->seek_;
    buffer.data_.assign(this->data_.begin(), this->data_.end());
    return buffer;
}

void Buffer::Reserve(size_t size) {
    this->data_.resize(this->GetSize() + size);
}

byte* Buffer::At(size_t index) {
    return this->data_.data() + index;
}

byte* Buffer::AtBegin() {
    return this->At(0);
}

byte* Buffer::AtCurrent() {
    return this->At(this->seek_);
}

byte* Buffer::AtEnd() {
    return this->At(this->GetSize());
}

std::vector<byte>& Buffer::Data() {
    return this->data_;
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

void Buffer::SetSeek(size_t seek) {
    assert(0 <= seek && seek <= this->GetSize());
    this->seek_ = seek;
}

void Buffer::SetSize(size_t size) {
    this->data_.resize(size);

    if (this->seek_ > size)
        this->seek_ = size;
}

void Buffer::Clear() {
    SetSize(0);
}

void Buffer::Read(byte* destination, size_t size) {
    assert(this->GetSeek() + size <= this->GetSize());
    memcpy(destination, this->AtCurrent(), size);
    this->seek_ += size;
}

void Buffer::Append(byte* source, size_t size) {
    this->Reserve(size);
    memcpy(this->AtEnd() - size, source, size);
}

std::istream& operator>>(std::istream& in, Buffer& buffer) {
    // Current position in stream
    std::streampos pos  = in.tellg();

    // Remaining count of bits to read
    std::size_t stream_size = static_cast<std::size_t>(GetRemainingSize(in));

    // Extending of buffer.data & writing from stream
    buffer.Reserve(stream_size);
    in.read(reinterpret_cast<char*>(buffer.AtEnd()) - stream_size, stream_size);

    return in;
}

std::ostream& operator<<(std::ostream& out, Buffer& buffer) {
    if (buffer.GetSize() > 0) {
        out.write(reinterpret_cast<char*>(buffer.AtCurrent()), buffer.GetLeft());
    }

    return out;
}

Buffer& operator>>(Buffer& buffer, Atomic&  atomic) {
    buffer.Read(atomic.GetData(), atomic.GetSize());
    return buffer;
}

Buffer& operator>>(Buffer& buffer, Atomic&& atomic) {
    buffer.Read(atomic.GetData(), atomic.GetSize());
    return buffer;
}

Buffer& operator<<(Buffer& buffer, Atomic&& atomic) {
    buffer.Append(atomic.GetData(), atomic.GetSize());
    return buffer;
}

Buffer& operator<<(Buffer& destination, Buffer& source) {
    destination.Append(source.AtCurrent(), source.GetLeft());
    return destination;
}