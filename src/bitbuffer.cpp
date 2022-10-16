#include "bitbuffer.h"

BitBuffer:: BitBuffer(): seek_(0), size_(0){}
BitBuffer::~BitBuffer(){}

void BitBuffer::SetData(std::vector<char>* data) {
    this->data_ = data;
}

bool BitBuffer::Get(size_t index) const {
    assert(index <= this->size_);

    return (this->data_->at(index/8) >> (index%8));
}

void BitBuffer::Set(size_t index, bool value) {
    assert(index <= this->size_);

    if (this->Get(index) != value) {
        this->data_->at(index/8) ^= ((char)(1<<index%8));
    }
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

    if (this->seek_ > size)
        this->seek_ = size;
}

void BitBuffer::Clear() {
    SetSize(0);
}

bool BitBuffer::operator[](size_t index) const {
    return this->Get(index);
}