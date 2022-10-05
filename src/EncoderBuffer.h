#pragma once

#include <iostream>
#include "Utilities.h"

class EncoderBuffer {
private:
    char* _begin, * _end;

public:
    EncoderBuffer();

    ~EncoderBuffer();

    char* begin() const;
    char* end() const;

    friend std::istream& operator>>(std::istream&, EncoderBuffer&);
    friend std::ostream& operator<<(std::ostream&, EncoderBuffer&);
};
