#pragma once
#include "../Encoder.h"
#include "../EncoderBuffer.h"

class HaffmanEncoder : public Encoder {
    EncoderBuffer encode() override;
    EncoderBuffer decode() override;
};