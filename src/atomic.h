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

    void  Free();
    bool  Empty();
    char* GetData();
    char  GetSize();
    void  SetData(char* data);
    void  SetSize(char  size);
    void  Resize(char size);

    template<typename Atom>
    static Atomic Make(Atom atom) {
        Atomic atomic;
        atomic.SetData(reinterpret_cast<char*>(malloc(sizeof(Atom))));
        atomic.SetSize(sizeof(Atom));

        memcpy(atomic.GetData(), &atom, sizeof(Atom));

        return atomic;
    }
};