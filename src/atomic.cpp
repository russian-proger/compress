#include "atomic.h"

Atomic::Atomic() {
    this->data_ = nullptr;
    this->size_ = 0;
}

Atomic::Atomic(char size) {
    this->data_ = reinterpret_cast<char*>(malloc(size));
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

char* Atomic::GetData() {
    return this->data_;
}

char Atomic::GetSize() {
    return this->size_;
}

void Atomic::SetSize(char size) {
    this->size_ = size;
}

void Atomic::SetData(char* data) {
    this->data_ = data;
}

void Atomic::Resize(char size) {
    this->Free();
    this->data_ = reinterpret_cast<char*>(malloc(size));
    this->size_ = size;
}