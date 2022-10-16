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
    this->free();
}

bool Atomic::empty() {
    return this->data_ == nullptr || this->size_ == 0;
}

void Atomic::free() {
    if (this->data_ != nullptr) {
        delete[] this->data_;
        this->data_ = nullptr;
        this->size_ = 0;
    }
}

char* Atomic::getData() {
    return this->data_;
}

char Atomic::getSize() {
    return this->size_;
}

void Atomic::resize(char size) {
    this->free();
    this->data_ = reinterpret_cast<char*>(malloc(size));
    this->size_ = size;
}

template<typename Atom>
Atomic Atomic::make(Atom atom) {
    Atomic atomic;
    atomic.data_ = reinterpret_cast<char*>(malloc(sizeof(Atom)));
    atomic.size_ = sizeof(Atom);

    memcpy(atomic.data_, &atom, sizeof(Atom));

    return atomic;
}