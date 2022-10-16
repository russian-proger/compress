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
    void  setData(char* data);
    void  setSize(char  size);
    void  resize(char size);

    template<typename Atom>
    static Atomic Make(Atom atom) {
        Atomic atomic;
        atomic.setData(reinterpret_cast<char*>(malloc(sizeof(Atom))));
        atomic.setSize(sizeof(Atom));

        memcpy(atomic.getData(), &atom, sizeof(Atom));

        return atomic;
    }
};