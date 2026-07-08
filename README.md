# VoltEngine

A simple, framework-free AI engine built from scratch in C++.

## Current Available Models
* None

## Project Status
Currently working on the 1B Parameters LLM's BPE tokenizer.

## Current Setup
* Reads line-by-line from dataset.txt and finds the most frequent pairs, merges them and writes out to "vocab.model" with their own index.

## How to Run the tokenizer
```bash
clang++ tokenizer.cpp -o token && ./token
```

**Mentorship**: Developed with the help of Gemini as a virtual mentor for learning the the math under the hood of the enigne and C++ syntax.
