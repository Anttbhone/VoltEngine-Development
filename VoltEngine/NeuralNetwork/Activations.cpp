#include "Activations.h"
#include <cmath>

void Activations::silu(Tensor& tensor) {
    for (size_t i = 0; i < tensor.data.size(); i++) {
        float x = tensor.data[i];
        tensor.data[i] = x * (1.0f / (1.0f + std::exp(-x)));
    }
}

void Activations::softmax(Tensor& tensor) {
    float max_val = tensor.data[0];
    for (int i = 0; i < tensor.data.size(); i++) {
        if (tensor.data[i] > max_val) {
            max_val = tensor.data[i];
        }
    }
    float sum_exp = 0.0f;
    for (size_t i = 0; i < tensor.data.size(); i++) {
        tensor.data[i] = std::exp(tensor.data[i] - max_val);
        sum_exp += tensor.data[i];
    }
    for (int i = 0; i < tensor.data.size(); i++) {
        tensor.data[i] /= sum_exp;
    }
}