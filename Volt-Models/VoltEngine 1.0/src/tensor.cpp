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
};
int main() {
    Tensor matrix(2, 3);
    matrix.at(1, 1) = 7.5;
    matrix.print();
    return 0;
}