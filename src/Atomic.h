#include <malloc.h>
#include <memory.h>

class Atomic {
private:
    char* data;
    char  size;

    void free();
public:
    Atomic();
    Atomic(char size);
    ~Atomic();

    char* getData();
    char  getSize();

    template<typename Atom>
    static Atomic make(Atom value);
};