#pragma once

#include <assert.h>
#include <iostream>
#include <sstream>
#include <vector>

#include "atomic.h"
#include "utilities.h"

class Buffer {
private:
    // Stores stream bytes
    std::vector<char> data_;

    // Current pointer position
    size_t seek_;

    void Reserve(size_t size);

public:
    Buffer();
    ~Buffer();

    char* At(size_t index);
    char* AtCurrent();
    char* GetPointerBegin();
    char* GetPointerEnd();

    size_t GetSize() const;
    size_t GetSeek() const;
    size_t GetLeft() const;

    void Read (char* destination, size_t size);
    void Write(char* source,      size_t size);

    char operator[](size_t index) const;

    friend std::istream& operator>>(std::istream&, Buffer&);
    friend std::ostream& operator<<(std::ostream&, Buffer&);

    friend Buffer& operator>>(Buffer&, Atomic& atomic);
    friend Buffer& operator<<(Buffer&, Atomic& atomic);
};