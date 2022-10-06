#pragma once

#include <iostream>
#include <fstream>
#include <cstddef>

struct Data {
	char *ptr;
	std::size_t size;
	
	Data(char *ptr, std::size_t size);
};

bool exists(std::string fname);
std::streamsize getRemainingSize(std::istream& stream);