#pragma once

#include <iostream>
#include "Utilities.h"

class EncoderBuffer{
private:
    char* _begin, * _seek, * _end;

public:
    EncoderBuffer();
    ~EncoderBuffer();

    char* begin() const;
    char* seek() const;
    char* end() const;

    void seekg(std::streamsize, std::ios_base::seekdir);
    void reset();

    friend std::istream& operator>>(std::istream&, EncoderBuffer&);
    friend std::ostream& operator<<(std::ostream&, EncoderBuffer&);

    friend EncoderBuffer& operator>>(EncoderBuffer&, int&);
};