#include "huffman_compressor.h"

 // how many time symbol meets in buffer
size_t freq[256];

 // position numbers
byte posx[256];

// Huffman Codes (in binary view)
BitBuffer code[256];

// calculates heights for each of subsegment [l, r)
void CalcHeights(int l, int r) {
    if (r - l >= 1) return;

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

Buffer HuffmanCompressor::Encode() {
    Buffer ret_buffer;
    BitBuffer bit_buffer;
    Buffer& buffer = this->buffer_;

    std::fill(freq, freq + 256, 0);
    std::iota(posx, posx + 256, 0);

    for (int i = 0; i < 256; ++i) {
        code[i].Clear();
    }

    for (int i = 0; i < buffer.GetLeft(); ++i) {
        ++freq[(byte)*(buffer.AtCurrent() + i)];
    }

    std::sort(posx, posx + 256, [](size_t lhs, size_t rhs) {
        return freq[lhs] > freq[rhs];
    });

    int l = 0, r = 0;
    while (r < 256 && freq[posx[r]] != 0) {
        ++r;
    }

    CalcHeights(l,r);
    for (int i = 0; i < 256; ++i) {
        if (code[posx[i]].GetSize() == 0) continue;
    }

    for (size_t i = 0; i < buffer.GetLeft(); ++i) {
        byte letter = *(buffer.AtCurrent()+i);
        code[letter].Reset();
        bit_buffer << code[letter];
    }

    ret_buffer << Atomic::Make((byte)r);

    // Tree heights
    for (int i = 0; i < r; ++i) {
        ret_buffer << Atomic::Make((byte)code[posx[i]].GetSize());
    }

    // For certain symbols
    for (int i = 0; i < r; ++i) {
        ret_buffer << Atomic::Make((byte)posx[i]);
    }

    // Size of compressed code
    ret_buffer << Atomic::Make(bit_buffer.GetSize());

    // Encodeed code
    std::vector<byte> compressed_data = bit_buffer.GetData();
    ret_buffer.Append(compressed_data.data(), compressed_data.size());

    return ret_buffer;
}