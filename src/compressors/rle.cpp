#include "rle.h"

using namespace cmp;

void RLECompressor::Encode() {
    Buffer& source = *this->GetSource();
    byte* input = source.AtCurrent();
    int size = source.GetLeft();
    
    Buffer& output = *this->GetOutput();

    byte* end = source.AtEnd();
    for (auto i = source.AtCurrent(); i != end;) {
        byte* j = i+1;
        if (end - i >= 3 && *i == *(i+1) && *i == *(i+2)) {
            // Positive
            j += 2;
            byte cnt = 130;
            while (j != end && *j == *i && cnt < 255) ++cnt, ++j;
            *i = cnt;
            output.Append(i, 2);
        } else {
            // Negative
            byte cnt = 0;
            while (cnt < 127 && j != end && (end-j <= 2 || *j != *(j+1) || *j != *(j+2))) {
                ++cnt, ++j;
            }
            output << Atomic::Make(cnt);
            output.Append(i, cnt+1);
        }
        i = j;
    }
}

void RLECompressor::Decode() {
    Buffer& source = *this->GetSource();
    byte* input = source.AtCurrent();

    auto& vec_out = this->GetOutput()->Data();
    for (byte* i = input; i != source.AtEnd();) {
        if (*i >= 128) {
            // Positive
            *i -= 127;
            while ((*i)--) {
                vec_out.push_back(*(i+1));
            }
            i += 2;
        } else {
            *i += 1;
            for (int j = 1; j <= *i; ++j) {
                vec_out.push_back(*(i+j));
            }
            i += *i + 1;
        }
    }
}