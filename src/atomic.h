#pragma once
#include <malloc.h>
#include <memory.h>

class Atomic {
private:
    char* data_;
    char  size_;

public:
    Atomic();
    Atomic(char size);
    ~Atomic();

    void  free();
    bool  empty();
    char* getData();
    char  getSize();
    void  resize(char size);

    template<typename Atom>
    static Atomic make(Atom value);
};