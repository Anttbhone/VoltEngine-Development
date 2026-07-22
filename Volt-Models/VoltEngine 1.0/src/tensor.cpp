#include <iostream>
#include <vector>
#include <cmath>
class Tensor {
public:

    std::vector<float> data;

    int rows;
    int cols;

    Tensor(int r, int c) : rows(r), cols(c), data(r * c, 0.0f) {}
    float& at(int r, int c) {
        int index = (r * cols) + c;
        return data[index];
    }

    void print() {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
            std::cout << at(r, c) << " ";
            }
        std::cout << "\n";
        }
    }

    Tensor matmul(Tensor& other) {
        if (this->cols != other.rows) {
            std::cout << "Error: Cant perform matmul.";
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
    void silu() {
        for (int i = 0; i < data.size(); i++) {
            float x = data[i];
            data[i] = x * 1.0f / (1.0f + std::exp(-x));
        }
    }

    void softmax() {
        for (int i = 0; i < data.size(); i++) {
            float max_val = data[0];
            float sum_exp = 0.0f;
            for (int i = 0; i < data.size(); i++) {
                data[i] = data[i] - std::exp(max_val) + sum_exp;
                data[i] /= sum_exp;
            }
        }
    }
};
int main() {
    Tensor test(1, 3);
    test.at(0, 0) = -2.0f;
    test.at(0, 1) = 0.0f;
    test.at(0, 2) = 2.0f;
    test.silu();
    test.print();
    return 0;
}