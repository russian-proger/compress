#include "huffman_compressor.h"

 // how many time symbol meets in buffer
size_t freq[256];

 // position numbers
byte posx[256];

// Huffman Codes (in binary view)
BitBuffer code[256];

// calculates heights for each of subsegment [l, r)
void CalcHeights(int l, int r) {
    if (r - l <= 1) return;

    int x = l;
    size_t sum = 0;
    size_t cur = 0;

    for (int i = l; i < r; ++i) {
        sum += freq[posx[i]];
    }

    while (cur*2 <= sum) cur += freq[posx[x++]];
    if (cur - freq[posx[x-1]] > sum - cur) --x;

    for (int i = l; i < r; ++i) {
        code[posx[i]] << (i >= x);
    }

    CalcHeights(l, x);
    CalcHeights(x, r);
}

void HuffmanCompressor::Encode() {
    BitBuffer bit_buffer;
    Buffer& source = *this->source_;
    Buffer& output = *this->output_;

    std::fill(freq, freq + 256, 0);
    std::iota(posx, posx + 256, 0);

    for (int i = 0; i < 256; ++i) {
        code[i].Clear();
    }

    for (int i = 0; i < source.GetLeft(); ++i) {
        freq[*(source.AtCurrent() + i)]++;
    }

    std::sort(posx, posx + 256, [](size_t lhs, size_t rhs) {
        return freq[lhs] > freq[rhs];
    });

    int m = 0;
    while (m < 256 && freq[posx[m]] != 0) {
        ++m;
    }

    CalcHeights(0,m);
    for (int i = 0; i < 256; ++i) {
        if (code[posx[i]].GetSize() == 0) continue;
    }

    for (size_t i = 0; i < source.GetLeft(); ++i) {
        byte letter = *(source.AtCurrent()+i);
        code[letter].ResetSeek();
        bit_buffer << code[letter];
    }

    output << Atomic::Make((byte)m);

    // Tree heights
    for (int i = 0; i < m; ++i) {
        output << Atomic::Make((byte)code[posx[i]].GetSize());
    }

    // For certain symbols
    for (int i = 0; i < m; ++i) {
        output << Atomic::Make((byte)posx[i]);
    }

    // Size of compressed code
    output << Atomic::Make(bit_buffer.GetSize());

    // Encoded code
    std::vector<byte>* compressed_data = bit_buffer.GetData();
    output.Append(compressed_data->data(), compressed_data->size());
}