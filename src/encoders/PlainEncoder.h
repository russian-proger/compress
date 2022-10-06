#pragma once
#include "../Encoder.h"
#include "../EncoderBuffer.h"

class PlainEncoder : public Encoder {
    EncoderBuffer encode() override;
    EncoderBuffer decode() override;
};