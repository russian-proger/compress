#pragma once

#include <assert.h>
#include <iostream>
#include <sstream>
#include "Utilities.h"

class Buffer {
private:
    char* _begin, * _seek, * _end;

public:
    Buffer();
    ~Buffer();

    char* begin() const;
    char* seek() const;
    char* end() const;

    void seekg(std::streamsize, std::ios_base::seekdir);
    void reset();

    friend std::istream& operator>>(std::istream&, Buffer&);
    friend std::ostream& operator<<(std::ostream&, Buffer&);

    friend Buffer& operator>>(Buffer&, int&);
    Buffer& operator=(Buffer&);
};