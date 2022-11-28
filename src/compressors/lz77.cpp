#include "lz77.h"

using namespace cmp;

static const int64_t WINDOW_SIZE = 128;

void LZ77Compressor::Encode() {
    Buffer& source = *this->source_;
    auto& vec_out = this->output_->Data();

    for (byte* i = source.AtCurrent(); i < source.AtEnd(); ++i) {
        int best = 0;
        int cnt = 0;
        int offset = 0;
        int lim = std::min(WINDOW_SIZE, i-source.AtCurrent());

        while (++offset < lim) {
            int size = 0;
            while (i+size < source.AtEnd()-1 && size < WINDOW_SIZE && *(i-offset + size%offset) == *(i+size))
                ++size;
            if (size > cnt) {
                cnt = size;
                best = offset;
            }
        }
        i += cnt;
        vec_out.push_back(best);
        vec_out.push_back(cnt);
        vec_out.push_back(*i);
    }
}

void LZ77Compressor::Decode() {
    Buffer& source = *this->source_;
    auto& vec_out = this->output_->Data();
    
    for (byte* i = source.AtCurrent(); i < source.AtEnd();) {
        int offset = *(i++);
        int length = *(i++);
        int letter = *(i++);

        int index = vec_out.size() - offset;
        for (int j = 0; j < length; ++j) {
            vec_out.push_back(vec_out[index + j % offset]);
        }
        vec_out.push_back(letter);
    }
}