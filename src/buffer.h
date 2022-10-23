#pragma once

#include <assert.h>
#include <vector>

#include "byte.h"
#include "atomic.h"
#include "utilities.h"

using namespace compress;

class Buffer {
private:
    // Stores stream bytes
    std::vector<byte> data_;

    // Current pointer position
    size_t seek_;

    void Reserve(size_t size);

public:
    Buffer();
    ~Buffer();

    Buffer Clone();

    byte* At(size_t index);
    byte* AtBegin();
    byte* AtCurrent();
    byte* AtEnd();

    size_t GetSize() const;
    size_t GetSeek() const;
    size_t GetLeft() const;

    void SetSeek(size_t seek);
    void SetSize(size_t size);
    void Clear();

    void Read  (byte* destination, size_t size);
    void Append(byte* source,      size_t size);

    byte operator[](size_t index) const;

    friend std::istream& operator>>(std::istream&, Buffer&);
    friend std::ostream& operator<<(std::ostream&, Buffer&);

    friend Buffer& operator>>(Buffer& destination, Atomic& atomic);
    friend Buffer& operator<<(Buffer& destination, Atomic  atomic);

    friend Buffer& operator<<(Buffer& destination, Buffer  source);
};