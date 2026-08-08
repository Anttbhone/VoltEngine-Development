#pragma once
#include <vector>

class Tensor {
public:
    std::vector<float> data;
    std::vector<float> grad;
    bool requires_grad;
    int rows;
    int cols;
    Tensor(int r, int c);
    float& at(int r, int c);
    float& at_grad(int r, int c);
    void print();
    Tensor matmul(Tensor& other);
    void backward_matmul(Tensor& input, Tensor& weights, Tensor& output);

};