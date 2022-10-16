#pragma once

#include <assert.h>
#include <cstddef>
#include <vector>

class BitBuffer {
private:
    std::vector<char>* data_;
    size_t seek_, size_;

public:
    BitBuffer();
    ~BitBuffer();

    void SetData(std::vector<char>* data);

    bool Get(size_t index) const;
    void Set(size_t index, bool value);

    size_t GetSize() const;
    size_t GetSeek() const;
    size_t GetLeft() const;

    void SetSeek(size_t seek);
    void SetSize(size_t size);
    void Clear();

    bool operator[](size_t index) const;
};