#include "PlainEncoder.h"

EncoderBuffer PlainEncoder::encode() {
    return this->_source;
}

EncoderBuffer PlainEncoder::decode() {
    return this->_source;
}