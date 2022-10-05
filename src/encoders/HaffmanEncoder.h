#pragma once
#include "../Encoder.h"
#include "../EncoderBuffer.h"

class HaffmanEncoder {
    HaffmanEncoder();
    ~HaffmanEncoder();
    EncoderBuffer encode() ;
    EncoderBuffer decode() ;
};