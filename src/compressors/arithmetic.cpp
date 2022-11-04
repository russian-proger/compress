#include "arithmetic.h"

typedef long double ld;

using namespace cmp;

static uint32_t freq[256];
static ld       part[257];

void ArithmeticCompressor::Encode() {
    BitBuffer bitbuffer;
    Buffer& buffer = *this->buffer_;
    Buffer& output = *this->output_;
    Buffer& source = *this->source_;

    for (auto i = source.AtCurrent(); i != source.AtEnd(); ++i) {
        ++freq[*i];
    }

    uint32_t data_size = source.AtEnd() - source.AtCurrent();

    part[256] = 1;
    for (int i = 1; i < 256; ++i) {
        part[i] = part[i-1] + static_cast<ld>(freq[i-1]) / static_cast<ld>(data_size);
    }

    // [l, r)
    ld l = 0, r = 1;
    ld lt, rt;

    int wait = 0;
    for (auto i = source.AtCurrent(); i != source.AtEnd(); ++i) {
        lt = l + (r-l) * part[*i];
        rt = l + (r-l) * part[*i+1];
        l = (lt);
        r = (rt);

        while (r-l < 0.5) {
            if (r <= 0.5) {
                bitbuffer.Append(0);
                while (wait > 0) {
                    bitbuffer.Append(1);
                    wait--;
                }
                l *= 2;
                r *= 2;
            } else if (l >= 0.5) {
                bitbuffer.Append(1);
                while (wait > 0) {
                    bitbuffer.Append(0);
                    wait--;
                }
                l = l*2-1;
                r = r*2-1;
            } else if (r-l < 0.25) {
                wait++;
                r = r*2-0.5;
                l = l*2-0.5;
            }
            else break;
        }
    }

    ld x = (r+l)/2;
    std::cout << x << std::endl;
    for (int i = 0; i < 40; ++i) {
        bitbuffer.Append(x >= 0.5);

        if (x >= 0.5) {
            x -= 0.5;
        }

        x *= 2;
    }

    output.Append(reinterpret_cast<byte*>(&freq), 1024);
    output << Atomic::Make(std::move(data_size));
    
    std::vector<byte>& data = *bitbuffer.GetData();
    output.Append(data.data(), data.size());
}

void ArithmeticCompressor::Decode() {
    Buffer& buffer = *this->buffer_;
    Buffer& output = *this->output_;
    Buffer& source = *this->source_;

    uint32_t data_size;
    source.Read(reinterpret_cast<byte*>(&freq), 1024);
    source.Read(reinterpret_cast<byte*>(&data_size), 4);


    part[256] = 1;
    for (int i = 1; i < 256; ++i) {
        part[i] = part[i-1] + static_cast<ld>(freq[i-1]) / static_cast<ld>(data_size);
    }

    byte* input = source.AtCurrent();
    ld x = 0, t = 0.5;

    int needle=20;
    for (int i = 0; i < needle; ++i, t /= 2) {
        if (1&(input[i/8]>>(i%8))) x += t;
    }
    t *= 2;

    std::cout << x << std::endl;

    ld l=0, r=1, lt, rt, xt;
    int wait = 0;
    for (int readed_cnt = 0; readed_cnt < data_size; ++readed_cnt) {
        ld y = (x-l)/(r-l);
        int pos = std::upper_bound(part, part+257, y) - part - 1;

        lt = l + (r-l) * part[pos];
        rt = l + (r-l) * part[pos+1];
        l = std::move(lt);
        r = std::move(rt);

        while (r-l < 0.5) {
            if (r < 0.5) {
                l *= 2;
                r *= 2;
                x *= 2;
            } else if (l >= 0.5) {
                l = l*2-1;
                r = r*2-1;
                x = x*2-1;
            } else {
                r = r*2-0.5;
                l = l*2-0.5;
                x = x*2-0.5;
            }

            x += (1&(input[needle/8]>>(needle%8))) * t;
            needle++;
        }

        output << Atomic::Make((char)pos);
    }

}