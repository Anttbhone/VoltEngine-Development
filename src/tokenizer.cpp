#include <iostream>
#include <vector>

int main() {
    std::vector<int> vector;
    for (int i = 0; i < 10; i++) {
        vector.push_back(i);
    }
    for (int i = 0; i < 10; i++) {
        vector[i] *= 2;
    }
    return 0;
}