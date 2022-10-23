#include "atomic.h"

Atomic::Atomic() {
    this->data_ = nullptr;
    this->size_ = 0;
}

Atomic::Atomic(byte size) {
    this->data_ = reinterpret_cast<byte*>(malloc(size));
    this->size_ = size;
}

Atomic::~Atomic() {
    this->Free();
}

bool Atomic::Empty() {
    return this->data_ == nullptr || this->size_ == 0;
}

void Atomic::Free() {
    if (this->data_ != nullptr) {
        delete[] this->data_;
        this->data_ = nullptr;
        this->size_ = 0;
    }
}

byte* Atomic::GetData() {
    return this->data_;
}

byte Atomic::GetSize() {
    return this->size_;
}

void Atomic::SetSize(byte size) {
    this->size_ = size;
}

void Atomic::SetData(byte* data) {
    this->data_ = data;
}

void Atomic::Resize(byte size) {
    this->Free();
    this->data_ = reinterpret_cast<byte*>(malloc(size));
    this->size_ = size;
}