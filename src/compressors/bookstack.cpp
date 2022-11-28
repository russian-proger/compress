#include "bookstack.h"

using namespace cmp;

static byte STACK[256];


void BSCompressor::PrintInfo() {
    std::cout << "Book-Stack (Move-to-Front) Transform\n";
}

inline byte DeMoveUp(const byte &v) {
    int ret = STACK[v];
    for (int i = v; i > 0; --i) STACK[i] = std::move(STACK[i-1]);
    return STACK[0] = ret;
}

inline byte EnMoveUp(const byte &v) {
    int j = 0;
    while (STACK[j] != v) ++j;

    // std::move
    for (int i = j; i > 0; --i) STACK[i] = std::move(STACK[i-1]);
    STACK[0] = v;
    return j;
}

void BSCompressor::Encode() {
    Buffer& source = *this->GetSource();
    byte* input = source.AtCurrent();
    int size = source.GetLeft();
    
    auto& vec_out = this->GetOutput()->Data();

    std::iota(STACK, STACK + 256, 0u);

    byte* end = source.AtEnd();
    for (auto i = source.AtCurrent(); i != end; ++i) {
        vec_out.push_back(EnMoveUp(*i));
    }
}

void BSCompressor::Decode() {
    Buffer& source = *this->GetSource();
    byte* input = source.AtCurrent();

    std::iota(STACK, STACK + 256, 0);

    auto& vec_out = this->GetOutput()->Data();
    byte* end = source.AtEnd();
    for (byte* i = input; i != end; ++i) {
        vec_out.push_back(DeMoveUp(*i));
    }
}