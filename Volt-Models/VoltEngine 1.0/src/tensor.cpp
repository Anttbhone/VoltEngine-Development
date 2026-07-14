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
};
int main() {
    Tensor matrix(2, 3);
    matrix.at(1, 1) = 7.5;
    std::cout << matrix.at(1, 1);
    return 0;
}