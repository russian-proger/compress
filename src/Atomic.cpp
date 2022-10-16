#include "Atomic.h"

Atomic::Atomic() {
    data = nullptr;
    size = 0;
}

Atomic::Atomic(char _size) {
    this->data = reinterpret_cast<char*>(malloc(size));
    this->size = _size;
}

Atomic::~Atomic() {
    this->free();
}

void Atomic::free() {
    if (this->data != 0) {
        delete[] this->data;
        this->data = nullptr;
        this->size = 0;
    }
}

char* Atomic::getData() {
    return this->data;
}

char Atomic::getSize() {
    return this->size;
}

template<typename Atom>
Atomic Atomic::make(Atom atom) {
    Atomic atomic;
    atomic.data = reinterpret_cast<char*>(malloc(sizeof(Atom)));
    atomic.size = sizeof(Atom);

    memcpy(atomic.data, &atom, sizeof(Atom));

    return atomic;
}