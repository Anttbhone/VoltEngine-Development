#include <iostream>
#include <vector>
#include <random>
#include <cmath>
int get_index(int row, int col, int total_col) {
    int index = (row * total_col) + col;
    return index;
}
float sigmoid(float x) {
    return 1.0f / (1.0f + std::exp(-x));
}
int main() {
    int i = 0;
    std::mt19937 gen(42);
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    std::vector<float> xor_inputs = {
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f
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
    std::vector<float> hidden_layer(12, 0.0f);
    std::vector<float> output_layer(4, 0.0f);
    std::vector<float> dw1(6, 0.0f);
    std::vector<float> dw2(3, 0.0f);
    std::vector<float> db1(3, 0.0f);
    std::vector<float> db2(1, 0.0f);
    std::vector<float> output_errors(4, 0.0f);
    for (i = 0; i < w1.size(); i++) {
        w1[i] = dist(gen);
    }
    for (i = 0; i < w2.size(); i++) {
        w2[i] = dist(gen);
    }
    std::cout << "--- Dataset Verification ---\n";
    for (int r = 0; r < 4; r++) {
        std::cout << "Xor Input: ";
        for (int c = 0; c < 2; c++) {
            int index = get_index(r, c, 2);
            std::cout << xor_inputs[index] << " ";
        }
        std::cout << "| Xor Target: " << xor_target[r] << "\n";
    }
    std::cout << "\n--- Computing Hidden Layer Outputs ---\n";
    for (int r = 0; r < 4; r++) {
        for (int h = 0; h < 3; h++) {
            float dot_product = 0;
            for (int i = 0; i < 2; i++) {
                int input_box = get_index(r, i, 2);
                int weight_box = get_index(i, h, 3);
                dot_product += xor_inputs[input_box] * w1[weight_box];
            }
            dot_product += b1[h];
            int hidden_box = get_index(r, h, 3);
            hidden_layer[hidden_box] = sigmoid(dot_product);
        }
    }
    std::cout << "\n--- Computing Final AI Guesses ---\n";
    for (int r = 0; r < 4; r++) {
        float out_dot_product = 0.0f;
        for (int h = 0; h < 3; h++) {
            int hidden_box = get_index(r, h, 3);
            int weight_box = get_index(h, 0, 1); // w2 is 3 rows x 1 col
            out_dot_product += hidden_layer[hidden_box] * w2[weight_box];
        }
        out_dot_product += b2[0];
        output_layer[r] = sigmoid(out_dot_product);
        std::cout << "Scenario " << r << " AI Guess: " << output_layer[r] 
                  << " | Correct Target: " << xor_target[r] << "\n";
    }
    float total_loss = 0;
    for (int r = 0; r < 4; r++) {
        float error = xor_target[r] - output_layer[r];
        total_loss += error * error;
    }
    total_loss /= 4.0f;
    std::cout << "Total Loss: " << total_loss << "\n";
    for (int r = 0; r < 4; r++) {
        float guess = output_layer[r];
        float target = xor_target[r];
        output_errors[r] = (guess - target) * guess * (1.0f - guess);
        std::cout << "Row " << r << " | Gradient Error Delta: " << output_errors[r] << "\n";
    }
    return 0;
}