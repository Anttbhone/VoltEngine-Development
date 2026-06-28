# VoltEngine

A simple, framework-free AI engine built from scratch in C++.

## Project Status
I paused the 1B parameter model due to hardware limits and the tough learning curve. I am starting with a small 100-parameter AI to solve the XOR problem. This will help me learn how forward passing, weights, biases, and backpropagation work under the hood.

## Current Setup
* **Inputs**: 2 numbers (like 1 and 0)
* **Hidden Brain Nodes**: 4 nodes
* **Output**: 1 final guess (should be 0 or 1)

## How to Run It
```bash
g++ main.cpp -o volt_engine
./volt_engine
```

**Mentorship**: Developed with the help of Gemini as a virtual mentor for learning the the math under the hood of the enigne and C++ syntax.