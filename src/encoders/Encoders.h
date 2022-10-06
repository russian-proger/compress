#include <vector>
#include "HaffmanEncoder.h"
#include "PlainEncoder.h"

std::vector<Encoder*> encoders = {
    new PlainEncoder(),
    new HaffmanEncoder()
};