#include "arithmetic2.h"

using namespace cmp;

static uint32_t freq[256];
static uint32_t part[257];

void Arithmetic2Compressor::Encode() {
    Buffer& source = *this->source_;
    Buffer& output = *this->output_;

    std::vector<byte>& out_vec = output.Data();

    uint64_t data_size = source.AtEnd() - source.AtCurrent();

    std::fill(freq, freq + 256, 0);

    for (auto i = source.AtCurrent(); i != source.AtEnd(); ++i) {
        ++freq[*i];
    }

    part[0] = 0;
    for (int i = 1; i <= 256; ++i) part[i] = part[i-1] + freq[i-1];

    uint64_t l = 0, r = UINT64_MAX;
    uint64_t lt, rt, d;

    const uint64_t HALF = (1ull<<63);
    int counter = 0;

    output.Append(reinterpret_cast<byte*>(&freq), 1024);
    output << Atomic::Make(static_cast<int>(source.GetLeft()));

    uint64_t last[2], after=0;

    // [8 bits] [15 bits] [39 bits]
    for (auto i = source.AtCurrent(); i != source.AtEnd(); ++i) {
        uint64_t kl = part[*i];
        uint64_t kr = part[*i+1];

        d  = r - l;
        r  = l + d / data_size * kr + d % data_size * kr / data_size;
        l +=     d / data_size * kl + d % data_size * kl / data_size;

        while ((d >> 39) == 0) {
            if (after != 0 && (l^r) >> 63 == 0) {
                int t = l>>63;
                l ^= (1ull<<63);
                r ^= (1ull<<63);
                out_vec.push_back(last[t]);
                t = (!t) * 0xff;
                while (--after) {
                    out_vec.push_back(t);
                }
            }

            if (((l^r)>>56) == 0) {
                // Common prefix
                out_vec.push_back(l>>56);
                l <<= 8;
                r <<= 8;
            }
            else {
                // Diffirence moment
                if (after == 0) {
                    last[0] = l>>56;
                    last[1] = r>>56;
                }
                after++;
                counter++;
                l <<= 8;
                r <<= 8;
                l -= HALF;
                r += HALF;
            }
            d = r-l;
        }

    }

    std::cout << "Differences: " << counter << '\n';
    d = ReverseBits((l>>1) + (r>>1) + (l&r&1));
    output << Atomic::Make(d);
}

void Arithmetic2Compressor::Decode() {
    Buffer& output = *this->output_;
    Buffer& source = *this->source_;

    uint32_t data_size;
    source.Read(reinterpret_cast<byte*>(&freq), 1024);
    source.Read(reinterpret_cast<byte*>(&data_size), 4);

    part[0]   = 0;
    for (int i = 1; i <= 256; ++i) part[i] = part[i-1] + freq[i-1];


    uint64_t l = 0, r = UINT64_MAX;
    uint64_t lt, rt, d, dd, dk, xb;

    const uint64_t HALF  = (1ull<<63);
    const uint64_t HALF8 = (1ull<<55);

    byte* input = source.AtCurrent();

    std::vector<byte>& out_vec = output.Data();

    uint64_t x = ReverseBits(*reinterpret_cast<uint64_t*>(input));
    input += 8;

    for (int readed_cnt = 0; readed_cnt < data_size; ++readed_cnt) {
#ifdef DEBUG
        assert(l <= x && x <= r);
#endif

        d  = r - l;
        dd = d / data_size;
        dk = d % data_size;

        int lb = 0, rb = 256;
        xb = x - l;
        while (lb < rb - 1) {
            uint64_t pb = (lb + rb) / 2;
            uint64_t vb = dd * part[pb] + dk * part[pb] / data_size;

            if (vb <= xb) lb = pb;
            else rb = pb;
        }

        out_vec.push_back(lb);

        uint64_t kl = part[lb];
        uint64_t kr = part[rb];

        r  = l + d / data_size * kr + d % data_size * kr / data_size;
        l +=     d / data_size * kl + d % data_size * kl / data_size;

        while ((d >> 39) == 0) {
            if (((l^r)>>56) == 0) {
                // Common prefix
                l <<= 8;
                r <<= 8;
                x <<= 8;
                x |= *input;
                input++;
            }
            else {
                // Diffirence
                l -= HALF8;
                r -= HALF8;
                x -= HALF8;
                l <<= 8;
                r <<= 8;
                x <<= 8;
                x |= *input;
                input++;
            }
            d = r-l;
        }
    }
}
