#pragma once

#include <assert.h>
#include <cstddef>
#include <vector>

#include "byte.h"

class BitBuffer {
private:
    std::vector<cmp::byte>* data_;
    size_t seek_, size_;

public:
    BitBuffer();
    ~BitBuffer();

    BitBuffer Clone();
    void SetData(std::vector<cmp::byte>* data);
    std::vector<cmp::byte>* GetData();

    bool Get(size_t index) const;
    void Set(size_t index, bool value);


    size_t GetSize() const;
    size_t GetSeek() const;
    size_t GetLeft() const;

    void ResetSeek();
    void SetSeek(size_t seek);
    void SetSize(size_t size);
    void Clear();

    void Append(bool value);

    bool operator[](size_t index) const;
    friend BitBuffer& operator<<(BitBuffer& bit_buffer, bool value);
    friend BitBuffer& operator<<(BitBuffer& destination, BitBuffer& source);
};