#pragma once

#include "buffer.h"

enum ALGORITHM_TYPE {
    PLAIN_TEXT,
    HAFFMAN_CODE,
    ARITHMETIC_CODE,
    BW_TRANSFORM,
    BOOK_STACK_TRANSFORM,
};

class Compressor {
protected:
    Buffer buffer_;

public:
    Compressor();
    Compressor(Buffer);
    ~Compressor();

    virtual Buffer   Compress();
    virtual Buffer Decompress();

    void SetBuffer(Buffer);
    Buffer GetBuffer();
};