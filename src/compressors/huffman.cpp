#include "huffman.h"

using namespace cmp;

 // how many time symbol meets in buffer
uint32_t freq[256];

 // position numbers
byte posx[256];

// Huffman Codes (in binary view)
BitBuffer code[256];

// For Huffman-Tree
byte leaf[1024]; // Char code
bool term[1024]; // Is Leaf
uint16_t left [1024];
uint16_t right[1024];
uint16_t timer = 0;

// calculates heights for each of subsegment [l, r)
void CalcHeights(int l, int r, uint16_t v=0) {
    if (r - l <= 1) {
        term[v] = 1;
        leaf[v] = posx[l];
        return;
    }

    term[v] = 0;

    int x = l;
    uint32_t sum = 0;
    uint32_t cur = 0;

    for (int i = l; i < r; ++i) {
        sum += freq[posx[i]];
    }

    while (cur*2 <= sum) cur += freq[posx[x++]];
    if (cur - freq[posx[x-1]] > sum - cur) --x;

    for (int i = l; i < r; ++i) {
        code[posx[i]] << (i >= x);
    }

    CalcHeights(l, x, left[v] = ++timer);
    CalcHeights(x, r, right[v] = ++timer);
}

void HuffmanCompressor::Encode() {
    BitBuffer bit_buffer;
    Buffer& source = *this->source_;
    Buffer& output = *this->output_;

    std::fill(freq, freq + 256, 0);
    std::iota(posx, posx + 256, 0);

    for (size_t i = 0; i < 256; ++i) {
        code[i].Clear();
    }

    for (size_t i = 0; i < source.GetLeft(); ++i) {
        freq[*(source.AtCurrent() + i)]++;
    }

    std::sort(posx, posx + 256, [](const size_t& lhs, const size_t& rhs) {
        return freq[lhs] > freq[rhs];
    });

    size_t m = 0;
    while (m < 256 && freq[posx[m]] != 0) {
        ++m;
    }

    CalcHeights(0,m,timer=0);
    for (size_t i = 0; i < 256; ++i) {
        if (code[posx[i]].GetSize() == 0) continue;
    }

    for (size_t i = 0; i < source.GetLeft(); ++i) {
        byte& letter = *(source.AtCurrent()+i);
        code[letter].ResetSeek();
        bit_buffer << code[letter];
    }

    output.Append(reinterpret_cast<byte*>(freq), 1024);

    // Size of compressed code
    output << Atomic::Make((size_t)bit_buffer.GetSize());

    // Encoded code
    std::vector<byte>* compressed_data = bit_buffer.GetData();
    output.Append(compressed_data->data(), compressed_data->size());
}


void HuffmanCompressor::Decode() {
    Buffer& source = *this->source_;
    Buffer& output = *this->output_;

    std::iota(posx, posx + 256, 0);
    source.Read(reinterpret_cast<byte*>(freq), 1024);

    for (size_t i = 0; i < 256; ++i) {
        code[i].Clear();
    }

    std::sort(posx, posx + 256, [](const size_t& lhs, const size_t& rhs) {
        return freq[lhs] > freq[rhs];
    });

    size_t m = 0;
    while (m < 256 && freq[posx[m]] != 0) {
        ++m;
    }

    CalcHeights(0,m,timer=0);

    size_t size;
    source.Read(reinterpret_cast<byte*>(&size), 8);
    byte* data = source.AtCurrent();

    size_t pos = 0;
    while (pos < size-1) {
        short v = 0;
        while (!term[v]) {
            if (!GetBit(data, pos++)) {
                v = left[v];
            } else {
                v = right[v];
            }
        }

        output << Atomic::Make((byte)leaf[v]);
    }
}
