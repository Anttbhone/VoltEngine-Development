#include <iostream>
#include <vector>
#include <random>
int main() {
    int i = 0;
    std::mt19937 gen(42);
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    std::vector<float> xor_inputs = {
        1.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        0.0f,0.0f
    };
    std::vector<float> xor_target = {
        1.0f,
        1.0f,
        0.0f,
        0.0f
    };
    std::vector<float> w1(6, 0.0f);
    std::vector<float> w2(3, 0.0f);
    std::vector<float> b1(3, 0.0f);
    std::vector<float> b2(1, 0.0f);
    for (i = 0; i < w1.size(); i++) {
        w1[i] = dist(gen);
    }
    for (i = 0; i < w2.size(); i++) {
        w2[i] = dist(gen);
    }
    for (int r = 0; r < 4; r++) {
        std::cout << "Xor Input: ";
        for (int c = 0; c < 2; c++) {
            int index = (r * 2) + c;

            std::cout << xor_inputs[index];
        }

        std::cout << "| Xor Target: " << xor_target[r];
        std::cout << "\n";
    }
    std::cout << "\n";
    for (i = 0; i < w1.size(); i++) {
        std::cout << w1[i];
    }
}