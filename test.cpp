#include <iostream>
#include <cmath>
double sigmoid(double z) {
    return 1.0 / (1.0 + std::exp(-z));
}
int main() {
    double x1 = 1.0;
    double x2 = 0.0;
    double target = 1.0;
    double w1 = 0.5;
    double w2 = -0.2;
    double bias = 0.1;
    double lr = 0.1;
    std::cout << "starting train session\n";
    for (int epoch = 0; epoch < 500; epoch++) {
        double z = (x1 * w2)+(x2 + w2) + bias;
        double guess = sigmoid(z);
        double error = target - guess;
        if (epoch == 1 || epoch % 100 == 0) {
            std::cout << "epoch: " << epoch << "\n" << "guess: " << guess << "\n" << "error: " << error << "\n";
        }
        double delta = error * guess * (1 - guess);
        w1 = w1 + (lr * delta * x1);
        w2 = w2 + (lr * delta * x2);
        bias = bias + (lr * delta);
    }
    std::cout << "training finished\n";
    std::cout << "w1: " << w1 << "\n";
    std::cout << "w2: " << w2 << "\n";
    std::cout << "bias: " << bias << "\n";
    return 0;
}