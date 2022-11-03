#pragma once

#include <assert.h>
#include <vector>

#include "byte.h"
#include "atomic.h"
#include "utilities.h"

class Buffer {
private:
    // Stores stream cmp::bytes
    std::vector<cmp::byte> data_;

    // Current pointer position
    size_t seek_;

    void Reserve(size_t size);

public:
    Buffer();
    ~Buffer();

    Buffer Clone();

    cmp::byte* At(size_t index);
    cmp::byte* AtBegin();
    cmp::byte* AtCurrent();
    cmp::byte* AtEnd();

    size_t GetSize() const;
    size_t GetSeek() const;
    size_t GetLeft() const;

    void SetSeek(size_t seek);
    void SetSize(size_t size);
    void Clear();

    void Read  (cmp::byte* destination, size_t size);
    void Append(cmp::byte* source,      size_t size);

    cmp::byte operator[](size_t index) const;

    friend std::istream& operator>>(std::istream&, Buffer&);
    friend std::ostream& operator<<(std::ostream&, Buffer&);

    friend Buffer& operator>>(Buffer& source, Atomic&  atomic);
    friend Buffer& operator>>(Buffer& source, Atomic&& atomic);
    friend Buffer& operator<<(Buffer& destination, Atomic&& atomic);

    friend Buffer& operator<<(Buffer& destination, Buffer& source);
};