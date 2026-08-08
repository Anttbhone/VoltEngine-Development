#include "Tensor.h"
#include <iostream>
#include <vector>
#include <cmath>

Tensor::Tensor(int r, int c) 
    : rows(r), cols(c), data(r * c, 0.0f), grad(r * c, 0.0f), requires_grad(false) {}

float& Tensor::at(int r, int c) {
    int index = (r * cols) + c;
    return data[index];
}

float& Tensor::at_grad(int r, int c) {
    int index = (r * cols) + c;
    return grad[index];
}

void Tensor::print() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            std::cout << at(r, c) << " ";
        }
        std::cout << "\n";
    }
}

Tensor Tensor::matmul(Tensor& other) {
    if (this->cols != other.rows) {
        std::cout << "Error: Cant perform matmul.\n";
        return Tensor(0, 0);
    }
    int target_row = this->rows;
    int target_col = other.cols;
    Tensor result(target_row, target_col);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            float sum = 0.0f;
            for (int k = 0; k < this->cols; k++) {
                sum += this->at(i, k) * other.at(k, j);
            }
            result.at(i, j) = sum;
        }
    }
    return result;
}
void backward_matmul(Tensor& input, Tensor& weights, Tensor& output) {
    for (int i = 0; i < input.rows; i++) {
        for (int j = 0; j < input.cols; j++) {
            float grad_val = 0.0f;
            for (int k = 0; k < weights.cols; k++) {
                grad_val += output.at_grad(i, k) * weights.at(k, j);
            }
            input.at_grad(i, j) += grad_val;
        }
    }
    for (int i = 0; i < weights.rows; i++) {
        for (int j = 0; j < weights.cols; j++) {
            float grad_val = 0.0f;
            for (int k = 0; k < input.rows; k++) {
                grad_val += input.at(k, i) * output.at_grad(k, j);
            }
            weights.at_grad(i, j) += grad_val;
        }
    }
}
