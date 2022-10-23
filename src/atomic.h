#pragma once
#include <malloc.h>
#include <memory.h>

#include "byte.h"

using namespace compress;

class Atomic {
private:
    byte* data_;
    byte  size_;

public:
    Atomic();
    Atomic(byte size);
    ~Atomic();

    void  Free();
    bool  Empty();
    byte* GetData();
    byte  GetSize();
    void  SetData(byte* data);
    void  SetSize(byte  size);
    void  Resize(byte size);

    template<typename Atom>
    static Atomic Make(Atom atom) {
        Atomic atomic;
        atomic.SetData(reinterpret_cast<byte*>(new Atom()));
        atomic.SetSize(sizeof(Atom));

        memcpy(atomic.GetData(), &atom, sizeof(Atom));

        return atomic;
    }
};