#pragma once
#include "../Core/Tensor.h"

class Activations {
public:
    static void silu(Tensor& tensor);
    static void softmax(Tensor& tensor);
};