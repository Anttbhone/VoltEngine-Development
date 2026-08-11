VoltEngine is designed to feel high-level and innovative, drawing heavy inspiration from PyTorch's clean syntax while executing raw C++ under the hood.

### Creating and Initializing Tensors
You can seamlessly create matrix spaces, manipulate indices, and print them in a clean, human-readable format.

```cpp
#include "Tensor.h"

int main() {
    // Instantiate a 2x3 matrix
    Tensor matrix(2, 3);

    // Add float values into specific indices
    matrix.at(0, 0) = 1.5f;
    matrix.at(0, 1) = 2.0f;
    matrix.at(1, 2) = -0.5f;

    // Display formatted matrix structure
    matrix.print();
    
    return 0;
}
```
## Byte Pair Encoding (BPE) Tokenizer

Every Large Language Model needs a way to break human strings into compressed integer numbers before sending them to the `Tensor` engine. **VoltEngine** features a custom, pure C++ **Byte Pair Encoding (BPE) Tokenizer** built from scratch to encode text strings into token IDs and decode token arrays back into human text.

### Tokenizer Interface

```cpp
class BPETokenizer {
public:
    BPETokenizer();
    
    // Encodes raw string text into an optimized vector of numerical token IDs
    std::vector<int> encode(const std::string& text);
    
    // Decodes an array of token IDs back into standard text string
    std::string decode(const std::vector<int>& tokens);
};
```

### BPETokenizer: Text to Tokens & Back

You can immediately integrate the compiled tokenization pipeline with your model data flows using simple code execution blocks:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include "VoltEngine/BPETokenizer.h" // Replace with your header path

int main() {
    // 1. Initialize the framework tokenizer 
    BPETokenizer tokenizer;

    // 2. Encode human text into token sequences (sub-word IDs)
    std::string prompt = "The quick brown fox jumps over the lazy dog!";
    std::vector<int> token_ids = tokenizer.encode(prompt);

    std::cout << "--- ENCODING PROMPT ---" << std::endl;
    std::cout << "Original String: " << prompt << std::endl;
    std::cout << "Token IDs Array: [ ";
    for (int id : token_ids) {
        std::cout << id << " ";
    }
    std::cout << "]" << std::endl;

    // 3. Decode numerical tokens back into native C++ strings
    std::string recovered_text = tokenizer.decode(token_ids);

    std::cout << "\n--- DECODING TOKENS ---" << std::endl;
    std::cout << "Decoded Output : " << recovered_text << std::endl;

    return 0;
}
```


**Mentorship**: Developed with the help of Gemini as a virtual mentor for learning the the math under the hood of the enigne and C++ syntax. Trained and evaluated on paper first to master backpropagation math before migrating logic to C++ algorithms.
