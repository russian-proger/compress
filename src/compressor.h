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
    Buffer
        *source_, // Read  only
        *output_, // Write only
        *buffer_; // Read & Write


public:
    Compressor();
    ~Compressor();

    virtual void Encode();
    virtual void Decode();
    virtual void PrintInfo();

    Buffer* GetSource();
    Buffer* GetBuffer();
    Buffer* GetOutput();

    void SetSource(Buffer*);
    void SetBuffer(Buffer*);
    void SetOutput(Buffer*);

    void SetSource(Buffer&);
    void SetBuffer(Buffer&);
    void SetOutput(Buffer&);

};