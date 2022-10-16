#pragma once

#include "Buffer.h"

enum ALGORITHM_TYPE {
    PLAIN_TEXT,
    HAFFMAN_CODE,
    ARITHMETIC_CODE,
    BW_TRANSFORM,
    BOOK_STACK_TRANSFORM,
};

class Compressor {
protected:
    Buffer _buffer;

public:
    Compressor();
    Compressor(Buffer);
    ~Compressor();

    virtual Buffer   compress();
    virtual Buffer decompress();

    void setBuffer(Buffer);
    Buffer getBuffer();
};