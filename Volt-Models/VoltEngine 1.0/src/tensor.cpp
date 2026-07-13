#include <iostream>
#include <vector>
class Tensor {
public:
    std::vector<float> data;
    int rows;
    int cols;
    Tensor(int r, int c) : rows(r), cols(c), data(r * c, 0.0f) {}
};
int main() {
    return 0;
}