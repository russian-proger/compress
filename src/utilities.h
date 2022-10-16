#include <iostream>
#include <fstream>

bool Exists(std::string fname);

inline bool GetBit(bool* src, size_t index);

inline void SetBit(char* src, size_t index, bool value);

std::streamsize GetRemainingSize(std::istream& stream);