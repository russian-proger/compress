#include <iostream>
#include <fstream>

#include "byte.h"

using namespace compress;

bool Exists(std::string fname);

inline bool GetBit(bool* src, size_t index);

inline void SetBit(byte* src, size_t index, bool value);

std::streamsize GetRemainingSize(std::istream& stream);