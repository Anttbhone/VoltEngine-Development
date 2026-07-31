#include "Activitations.h"
#include <cmath>

void Activations::silu(Tensor& tensor) {
    for (size_t i = 0; i < tensor.data.size(); i++) {
        float x = tensor.data[i];
        tensor.data[i] = x * (1.0f / (1.0f + std::exp(-x)));
    }
}

void Activations::softmax(Tensor& tensor) {
    // Still not done yet!!!!!
}