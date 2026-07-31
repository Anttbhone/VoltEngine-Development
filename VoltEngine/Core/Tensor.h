#pragma once
#include <vector>

class Tensor {
public:
    std::vector<float> data;
    int rows;
    int cols;
    Tensor(int r, int c);
    float& at(int r, int c);
    void print();
    Tensor matmul(Tensor& other);
};