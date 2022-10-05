#pragma once

#include "EncoderBuffer.h"

enum ALGORITHM_TYPE {
    PLAIN_TEXT,
    HAFFMAN_CODE,
    ARITHMETIC_CODE,
    BW_TRANSFORM,
    BOOK_STACK_TRANSFORM,
};

class Encoder {
protected:
    EncoderBuffer _source;

public:
    Encoder();
    Encoder(EncoderBuffer);
    ~Encoder();

    virtual EncoderBuffer encode();
    virtual EncoderBuffer decode();

    void setEncoderBuffer(EncoderBuffer);
};