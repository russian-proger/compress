#include <iomanip>
#include <iostream>
#include <sys/time.h>
#include <vector>
#include <memory.h>

using namespace std;

struct T {
    int *a;
    T(int o){a = new int(o);}
};

void F(T t) {
    *t.a = 1;
}

int main () {
    char* t = new char[4];
    int v = 257;
    // memcpy(t, &v, sizeof(int));
    t = (char*)&v;

    for (int i = 0; i < 4; ++i) {
        cout << (int)t[i] << ' ';
    }
};
