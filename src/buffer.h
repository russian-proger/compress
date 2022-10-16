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

    Buffer Clone();

    char* At(size_t index);
    char* AtBegin();
    char* AtCurrent();
    char* AtEnd();

    size_t GetSize() const;
    size_t GetSeek() const;
    size_t GetLeft() const;

    void SetSeek(size_t seek);
    void SetSize(size_t size);
    void Clear();

    void Read  (char* destination, size_t size);
    void Append(char* source,      size_t size);

    char operator[](size_t index) const;

    friend std::istream& operator>>(std::istream&, Buffer&);
    friend std::ostream& operator<<(std::ostream&, Buffer&);

    friend Buffer& operator>>(Buffer& destination, Atomic& atomic);
    friend Buffer& operator<<(Buffer& destination, Atomic  atomic);

    friend Buffer& operator<<(Buffer& destination, Buffer  source);
};