#include "bwt.h"

using namespace cmp;

static constexpr size_t LIM = (1ull<<15);

void CountSort(const int &size, int *&SA, int *&RA, int *&tempSA, int *&cnt) {
    int ra_max = std::max(512, size);
    std::fill(cnt, cnt + ra_max, 0);

    for (int i = 0; i < size; ++i) ++cnt[RA[i]];
    for (int i = 1; i < ra_max; ++i) cnt[i] += cnt[i-1];
    for (int i = size-1; i >= 0; --i) {

#ifdef DEBUG
        assert(cnt[RA[SA[i]]] <= size);
#endif

        tempSA[--cnt[RA[SA[i]]]] = SA[i];
    }
    std::swap(tempSA, SA);
}

void BWTCompressor::Encode() {
    Buffer& source = *this->source_;

    std::vector<byte>& buf_vec = this->buffer_->Data();
    std::vector<byte>& out_vec = this->output_->Data();

    // Output offset
    int offset = 5;

    buf_vec.resize(LIM<<4);
    out_vec.resize(source.GetLeft() + (source.GetLeft() + LIM-2) / (LIM-1) * 4 + offset);

    // Input
    byte* beg = source.AtCurrent();
    byte* end = source.AtEnd();

    // Output
    byte* out = out_vec.data();

    *reinterpret_cast<int*>(out+1) = static_cast<int>(source.GetLeft());

    // Suffix Array
    int* SA     = reinterpret_cast<int*>(buf_vec.data());

    // Ranking Array
    int* RA     =     SA + LIM;

    // Temporary arrays
    int* tempSA =     RA + LIM;
    int* tempRA = tempSA + LIM;

    // Reading by chunks
    while (beg < end) {
        int len = std::min(static_cast<size_t>(end-beg), LIM-1);
        int size = len + 1;

        std::iota(SA, SA + size, 0);
        for (int i = 0; i < len; ++i) RA[i] = static_cast<int>(*(beg + i)) + 1;
        RA[len] = 0;

        CountSort(size, SA, RA, tempSA, tempRA);

        for (int k = 1; k < size && RA[SA[len]] != len; k <<= 1) {
            for (int i = 0; i < size; ++i) SA[i] = (SA[i] - k + size) % size;
            CountSort(size, SA, RA, tempSA, tempRA);

            tempRA[SA[0]] = 0;
            for (int i = 1; i < size; ++i) {
                tempRA[SA[i]] = tempRA[SA[i-1]] + (RA[SA[i-1]] != RA[SA[i]] || RA[(SA[i-1] + k) % size] != RA[(SA[i] + k) % size]);
            }

            std::swap(RA, tempRA);
        }

        // Output
        for (int i = 0, j = 0; i < size; ++i, ++j) {
            if (SA[i] == 0) {
                *reinterpret_cast<int*>(out + offset + len) = i;
                --j;
            } else {
                *(out + offset + j) = *(beg + (SA[i] + len) % size);
            }
        }

        beg    += len;
        offset += len + 4;
    }
}

void BWTCompressor::Decode() {
    Buffer& source = *this->source_;

    int data_size;
    source.Read(reinterpret_cast<byte*>(&data_size), 4);

    std::vector<byte>& buf_vec = this->buffer_->Data();
    std::vector<byte>& out_vec = this->output_->Data();

    // Output offset
    int offset = out_vec.size();

    buf_vec.resize(LIM<<4);
    out_vec.resize(data_size);

    // Input
    byte* beg = source.AtCurrent();
    byte* end = source.AtEnd();

    // Output
    byte* out = out_vec.data();

    // Suffix Array
    int* SA     = reinterpret_cast<int*>(buf_vec.data());

    // Ranking Array
    int* RA     =     SA + LIM;

    // Temporary arrays
    int* tempSA =     RA + LIM;
    int* tempRA = tempSA + LIM;

    // Reading by chunks
    while (beg < end) {
        int len = std::min(static_cast<size_t>(end-beg), LIM+3) - 4;
        int size = len + 1;
        int start = *reinterpret_cast<int*>(beg + len);

        std::iota(SA, SA + size, 0);
        for (int i = 0; i < start; ++i) RA[i] = static_cast<int>(*(beg + i)) + 1;
        for (int i = start+1; i < size; ++i) RA[i] = static_cast<int>(*(beg + i - 1)) + 1;
        RA[start] = 0;

        CountSort(size, SA, RA, tempSA, tempRA);

        for (int i = 0; i < size; ++i) {
            tempSA[SA[i]] = i;
        }

        int v = start;
        for (int i = 0; i < len; ++i) {
            v = tempSA[v];
            *(out + offset + len - i - 1) = *(beg + v - (v > start));
        }

        beg    += len + 4;
        offset += len;
    }
}