#include <iomanip>
#include <iostream>
#include <bitset>
#include <memory.h>
#include <sys/time.h>
#include <vector>

using namespace std;

struct T {
    int *a;
    T(int o){a = new int(o);}
};

void F(T t) {
    *t.a = 1;
}

int main () {
};
