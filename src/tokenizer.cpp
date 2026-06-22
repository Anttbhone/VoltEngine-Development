#include <iostream>
#include <vector>

int main() {
    std::vector<float> vector = {1,2,3,4};
    for (int i = 0; i < vector.size; i++;) {
        vector[i] += 5;
    }
    return 0;
}