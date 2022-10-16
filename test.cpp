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
    cout << sizeof(void);
};
