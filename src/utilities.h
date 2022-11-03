#pragma once

#include <iostream>
#include <fstream>

#include "byte.h"

namespace cmp {
    bool Exists(std::string fname);

    bool GetBit(byte* src, size_t index);

    void SetBit(byte* src, size_t index, bool value);

    std::streamsize GetRemainingSize(std::istream& stream);
}