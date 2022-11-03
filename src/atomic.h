#pragma once

#include <iostream>
#include <malloc.h>
#include <memory.h>

#include "byte.h"

class Atomic {
private:
    cmp::byte* data_;
    cmp::byte  size_;

public:
    Atomic();
    Atomic(cmp::byte size);
    ~Atomic();

    void  Free();
    bool  Empty();
    cmp::byte* GetData();
    cmp::byte  GetSize();
    void  SetData(cmp::byte* data);
    void  SetSize(cmp::byte  size);
    void  Resize (cmp::byte  size);

    template<typename Atom>
    static Atomic Make(Atom&& atom) { // Possibly one &
        Atomic atomic;
        atomic.SetData(reinterpret_cast<cmp::byte*>(new Atom()));
        atomic.SetSize(sizeof(Atom));

        memcpy(atomic.GetData(), &atom, sizeof(Atom));

        return atomic;
    }
};