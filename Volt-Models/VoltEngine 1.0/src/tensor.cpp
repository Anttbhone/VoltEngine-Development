#include <iostream>
#include <vector>
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


};
int main() {
    Tensor matrix(2, 3);
    matrix.at(1, 1) = 7.5;
    matrix.print();
    return 0;
}