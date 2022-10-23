#include "bitbuffer.h"

int counter = 0;
BitBuffer:: BitBuffer(): seek_(0), size_(0) {
    this->data_ = new std::vector<byte>();
}
BitBuffer::~BitBuffer(){}

BitBuffer BitBuffer::Clone() {
    BitBuffer bit_buffer;
    *bit_buffer.data_ = (*this->data_);
    bit_buffer.seek_ = this->seek_;
    bit_buffer.size_ = this->size_;
    return bit_buffer;
}

void BitBuffer::SetData(std::vector<byte>* data) {
    this->data_ = data;
}
std::vector<byte> BitBuffer::GetData() {
    return *this->data_;
}


bool BitBuffer::Get(size_t index) const {
    assert(this->data_ != nullptr);
    assert(index < this->size_);

    return 1 & (this->data_->at(index/8) >> (index%8));
}

void BitBuffer::Set(size_t index, bool value) {
    assert(index < this->size_);

    if (this->Get(index) != value) {
        this->data_->at(index/8) ^= ((byte)(1<<index%8));
    }
}

void BitBuffer::Reset() {
    this->seek_ = 0;
}

size_t BitBuffer::GetSize() const {
    return this->size_;
}

size_t BitBuffer::GetSeek() const {
    return this->seek_;
}

size_t BitBuffer::GetLeft() const {
    return this->GetSize() - this->GetSeek();
}

void BitBuffer::SetSeek(size_t seek) {
    assert(0 <= seek && seek <= this->GetSize());
    this->seek_ = seek;
}

void BitBuffer::SetSize(size_t size) {
    this->data_->resize((size+7)/8);

    this->size_ = size;
    if (this->seek_ > size)
        this->seek_ = size;
}

void BitBuffer::Clear() {
    SetSize(0);
}

void BitBuffer::Append(bool value) {
    if (this->size_ % 8 == 0) {
        this->data_->push_back(0);
    }
    this->size_++;
    this->Set(this->size_ - 1, value);
}

bool BitBuffer::operator[](size_t index) const {
    assert(index < this->size_);
    return this->Get(index);
}

BitBuffer& operator<<(BitBuffer& bit_buffer, bool value) {
    bit_buffer.Append(value);
    return bit_buffer;
}

BitBuffer& operator<<(BitBuffer& destination, BitBuffer source) {
    while (source.seek_ < source.size_) {
        destination << source[source.seek_];
        source.seek_++;
    }

    return destination;
}