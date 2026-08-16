# VoltEngine Design & API Documentation

**Project:** VoltEngine  
**Document:** Design & API Reference  
**Documentation Version:** v1.0.0  
**Project Status:** Development  
**Language:** C++  
**License:** MIT  
**Primary Goal:** A lightweight, low-level C++ framework for building and running small AI/ML systems without requiring a Python runtime.

---

## 1. Purpose

VoltEngine is a C++ AI/ML framework designed around direct, lightweight control of machine-learning components.

The project is intended to provide reusable building blocks for small neural networks and, eventually, larger systems such as a custom video-generation model.

VoltEngine is designed to keep the core implementation in C++ and avoid making a Python interpreter a runtime dependency.

This document describes the current API, intended behavior, architecture, and development status.

---

## 2. Documentation Conventions

Every documented function uses the following structure:

- **Version** — Version in which the function was introduced or last substantially changed.
- **Purpose** — What the function is intended to do.
- **Arguments** — Parameters accepted by the function.
- **How it works** — High-level description of the implementation.
- **Returns** — Return type and meaning.
- **Example** — Typical usage.
- **Status** — Whether the function is implemented, experimental, or planned.

Function documentation should be updated whenever the public behavior or signature changes.

---

# 3. BPETokenizer

## 3.1 `BPETokenizer()`

**Version:** v1.0.0  
**Status:** Implemented

### Purpose

Creates a BPE tokenizer and initializes its base vocabulary.

### Arguments

None.

### How it works

The constructor initializes:

- Byte tokens with IDs `0` through `255`
- `<PAD>` with ID `256`
- `<BOS>` with ID `257`
- `<EOS>` with ID `258`
- The next available BPE token ID as `259`

The tokenizer maintains two vocabulary maps:

```text
token text → token ID
token ID   → token text
```

### Returns

A constructed `BPETokenizer` object.

### Example

```cpp
BPETokenizer tokenizer;
```

---

## 3.2 `token_train()`

**Version:** v1.0.0  
**Status:** Implemented / Development

### Signature

```cpp
void token_train(
    int target_vocab_size,
    const std::string& dataset
);
```

### Purpose

Trains the BPE tokenizer using a dataset and expands the vocabulary toward the requested vocabulary size.

### Arguments

| Argument | Type | Description |
|---|---|---|
| `target_vocab_size` | `int` | Target number of vocabulary entries |
| `dataset` | `const std::string&` | Path to the dataset used for BPE training |

### How it works

1. Opens the dataset as a binary file.
2. Reads the dataset byte-by-byte.
3. Converts each byte into an initial token ID.
4. Searches the token sequence for adjacent token pairs.
5. Counts the occurrences of each pair.
6. Selects the most frequent pair.
7. Creates a new token from the two existing token strings.
8. Assigns the new token the next available token ID.
9. Replaces occurrences of the selected pair with the new token.
10. Removes the consumed token positions.
11. Repeats until the target vocabulary size is reached or no pair occurs more than once.

### BPE Token ID Range

The base vocabulary contains:

```text
0–255   Byte tokens
256     <PAD>
257     <BOS>
258     <EOS>
259+    BPE-created tokens
```

### Returns

`void`.

### Example

```cpp
BPETokenizer tokenizer;

tokenizer.token_train(300, "dataset.txt");
```

### Notes

The current implementation performs a straightforward pair scan over the token sequence. This is intentionally simple and is suitable for the initial implementation, but it may be optimized later for larger datasets.

---

## 3.3 `encode()`

**Version:** v1.0.0  
**Status:** Implemented

### Signature

```cpp
std::vector<int> encode(
    const std::string& text
);
```

### Purpose

Converts text into a sequence of token IDs using the tokenizer's current vocabulary.

### Arguments

| Argument | Type | Description |
|---|---|---|
| `text` | `const std::string&` | Text to tokenize |

### How it works

The encoder scans the input from left to right.

At each position it searches the vocabulary for the longest token that matches the current section of text.

When a match is found:

```text
text → token ID
```

The token ID is appended to the output vector and the input position advances by the matched token length.

If no vocabulary token matches, the current byte is used as its byte token ID.

### Returns

```cpp
std::vector<int>
```

A sequence of token IDs.

### Example

```cpp
std::vector<int> tokens = tokenizer.encode("Hello");
```

---

## 3.4 `decode()`

**Version:** v1.0.0  
**Status:** Implemented

### Signature

```cpp
std::string decode(
    const std::vector<int>& input_ids
);
```

### Purpose

Converts token IDs back into text.

### Arguments

| Argument | Type | Description |
|---|---|---|
| `input_ids` | `const std::vector<int>&` | Token IDs to decode |

### How it works

Each token ID is looked up in `inverse_vocab`.

The corresponding token string is appended to the output string.

### Returns

```cpp
std::string
```

The reconstructed text.

### Example

```cpp
std::vector<int> tokens = tokenizer.encode("Hello");
std::string text = tokenizer.decode(tokens);
```

---

## 3.5 `save_vocab()`

**Version:** v1.0.0  
**Status:** Implemented

### Signature

```cpp
void save_vocab(
    const std::string& filepath
);
```

### Purpose

Saves the current vocabulary to a file.

### Arguments

| Argument | Type | Description |
|---|---|---|
| `filepath` | `const std::string&` | Path of the vocabulary output file |

### How it works

The function iterates through the vocabulary and writes each token ID and token text to the specified file.

The conceptual file format is:

```text
TOKEN_ID TOKEN_TEXT
```

Example:

```text
256 <PAD>
257 <BOS>
258 <EOS>
```

Special newline and carriage-return tokens are escaped before being written.

### Returns

`void`.

### Example

```cpp
tokenizer.save_vocab("vocab.model");
```

---

## 3.6 `load_vocab()`

**Version:** v1.0.0  
**Status:** Planned / Not implemented

### Signature

```cpp
void load_vocab(
    const std::string& filepath
);
```

### Purpose

Loads a previously saved vocabulary into a `BPETokenizer`.

### Arguments

| Argument | Type | Description |
|---|---|---|
| `filepath` | `const std::string&` | Path to the vocabulary file |

### How it should work

The function should:

1. Open the vocabulary file.
2. Read each token ID and token text.
3. Reconstruct `vocab`.
4. Reconstruct `inverse_vocab`.
5. Restore the next available token ID.
6. Correctly restore escaped special characters.

### Returns

`void`.

### Example

```cpp
tokenizer.load_vocab("vocab.model");
```

### Status

This function is currently a design target and should not be considered implemented until the corresponding source code is complete and tested.

---

# 4. Neural Network API

The neural-network portion of VoltEngine is under development.

The planned API is intended to provide small reusable neural-network components rather than requiring users to manually implement the same mathematical operations repeatedly.

---

## 4.1 `Linear`

**Version:** Planned for v1.0.0  
**Status:** Planned

### Purpose

Provides a fully connected neural-network layer.

The intended mathematical operation is:

```text
y = xW + b
```

where:

- `x` is the input
- `W` is the weight matrix
- `b` is the bias
- `y` is the output

### Planned Interface

```cpp
Linear layer(input_features, output_features);
```

### Arguments

| Argument | Type | Description |
|---|---|---|
| `input_features` | `int` | Number of input features |
| `output_features` | `int` | Number of output features |

### Intended Use

```cpp
Linear layer(128, 64);
```

This represents a layer that accepts 128 features and produces 64 features.

### Status

Planned. The implementation should be added after the underlying tensor/matrix operations required by the layer are stable.

---

# 5. Activation Functions

Activation functions are intended to be reusable components for neural networks.

---

## 5.1 `sigmoid()`

**Version:** v1.0.0  
**Status:** Implemented

### Purpose

Applies the sigmoid activation function.

### Mathematical Definition

```text
sigmoid(x) = 1 / (1 + e^(-x))
```

### Behavior

Maps an input value into the range:

```text
0 < sigmoid(x) < 1
```

### Typical Use

Sigmoid can be used when an output is required to represent a value between zero and one.

---

## 5.2 `softmax()`

**Version:** v1.0.0  
**Status:** Implemented

### Purpose

Converts a collection of values, commonly called logits, into normalized probabilities.

### Behavior

Softmax produces values whose sum is approximately:

```text
1.0
```

### Typical Use

Softmax is commonly used for multi-class classification outputs.

---

# 6. Tensor System

The Tensor system is intended to provide the numerical data structures used by VoltEngine's neural-network components.

### Planned Responsibilities

The Tensor system should eventually support:

- Storage of numerical values
- Tensor dimensions/shapes
- Matrix multiplication
- Element-wise operations
- Broadcasting where appropriate
- Reshaping
- Basic indexing
- Operations required by neural-network layers

The exact API should be documented after the Tensor implementation stabilizes.

---

# 7. Training System

The training system is a future part of VoltEngine.

### Planned Components

```text
Model
 ├── Layers
 ├── Forward pass
 ├── Loss
 ├── Backward pass
 └── Optimizer
```

Potential components include:

- Forward propagation
- Loss functions
- Gradient calculation
- Backpropagation
- Optimizers
- Parameter updates
- Training loops
- Checkpoint saving/loading

These components should be added only after the numerical foundation is stable.

---

# 8. Model Architecture

VoltEngine is intended to allow users to build a model from reusable C++ components.

Conceptually:

```text
Input
  ↓
Tensor
  ↓
Linear
  ↓
Activation
  ↓
Linear
  ↓
Output
```

A future model could therefore be constructed from components such as:

```cpp
Linear
Activation
Linear
Softmax
```

rather than requiring every operation to be manually rewritten.

---

# 9. Future Video Generation System

One of the long-term goals of VoltEngine is to support a small video-generation model implemented and executed using the C++ framework.

### Target

Initial target:

```text
Model size: approximately 100M parameters
Target hardware: consumer hardware
Target GPU memory: approximately 8 GB VRAM
```

This is a development target rather than a current capability of VoltEngine.

### Planned Pipeline

A possible future architecture is:

```text
Text / Conditioning
        ↓
Tokenizer
        ↓
Embedding
        ↓
Neural Network
        ↓
Latent / Feature Representation
        ↓
Video Generation
        ↓
Frame Output
```

The exact architecture is intentionally undecided until the underlying framework is capable of training and running smaller neural networks reliably.

---

# 10. Design Principles

## 10.1 C++ First

VoltEngine is written primarily in C++.

The core framework should not require a Python interpreter to perform its fundamental operations.

## 10.2 Lightweight

The framework should avoid unnecessary dependencies where practical.

## 10.3 Reusable Components

Common operations should be implemented once and reused.

For example:

```cpp
Linear layer(128, 64);
```

should replace repeatedly writing the same matrix multiplication and bias logic.

## 10.4 Understandable Source

The implementation should remain understandable to developers who want to inspect how the framework works.

## 10.5 Modular Architecture

Components should be separated into logical modules:

```text
Tokenizer
Tensor
Layers
Activations
Losses
Optimizers
Models
Runtime
```

## 10.6 Consumer Hardware

VoltEngine is intended to explore efficient AI workloads on consumer hardware rather than assuming access to large server infrastructure.

---

# 11. User Levels

VoltEngine is intended to support different levels of users.

## User

A user who wants to use VoltEngine without modifying its internal implementation.

Typical workflow:

```text
Install
 ↓
Include VoltEngine
 ↓
Use public API
 ↓
Build model/application
```

## Advanced User

A user who wants to inspect, modify, extend, or rebuild the framework.

Advanced users may work directly with:

- Source code
- Internal classes
- Build configuration
- Tensor operations
- Model components
- Experimental features

The source distribution should therefore remain available for users who want deeper control.

---

# 12. Versioning

VoltEngine uses semantic versioning:

```text
MAJOR.MINOR.PATCH
```

Example:

```text
v1.0.0
```

### MAJOR

Incremented when incompatible API changes are introduced.

Example:

```text
v1.x.x → v2.0.0
```

### MINOR

Incremented when new backward-compatible functionality is added.

Example:

```text
v1.0.0 → v1.1.0
```

### PATCH

Incremented for backward-compatible fixes.

Example:

```text
v1.0.0 → v1.0.1
```

---

# 13. API Stability

Functions should be considered experimental until the framework reaches a stable release.

A function may change its:

- Name
- Parameters
- Return type
- Internal behavior
- File location

during development.

Stable APIs should only be promised after they have been tested and reviewed.

---

# 14. Current Development Status

### Implemented

- [x] `BPETokenizer`
- [x] Base byte vocabulary
- [x] Special tokens
- [x] BPE training prototype
- [x] `encode()`
- [x] `decode()`
- [x] `save_vocab()`
- [x] Sigmoid
- [x] Softmax

### In Development

- [ ] Vocabulary loading
- [ ] Tensor system
- [ ] Matrix operations
- [ ] `Linear`
- [ ] Neural-network model structure
- [ ] Loss functions
- [ ] Backpropagation
- [ ] Optimizers
- [ ] Model serialization

### Long-Term

- [ ] Small-model training
- [ ] GPU acceleration
- [ ] CUDA backend
- [ ] Model inference runtime
- [ ] Approximately 100M-parameter model experiments
- [ ] Video-generation model experiments

---

# 15. Example End-to-End Tokenizer Workflow

```cpp
#include "BPE.h"

int main()
{
    BPETokenizer tokenizer;

    tokenizer.token_train(300, "dataset.txt");

    tokenizer.save_vocab("vocab.model");

    std::vector<int> tokens = tokenizer.encode("Hello");

    std::string text = tokenizer.decode(tokens);

    return 0;
}
```

The intended workflow is:

```text
Create tokenizer
      ↓
Train tokenizer
      ↓
Save vocabulary
      ↓
Encode text
      ↓
Run model
      ↓
Decode output
```

---

# 16. Documentation Maintenance

When adding a public function to VoltEngine:

1. Add the function to the appropriate header.
2. Implement the function.
3. Test the function.
4. Add its documentation to this file.
5. Record its version.
6. Add an example.
7. Update the development-status section if necessary.

Documentation should describe the actual behavior of the implementation, not only the intended behavior.

If a function is not implemented, mark it as:

```text
Status: Planned / Not implemented
```

This prevents the documentation from claiming that VoltEngine supports functionality that does not yet exist.

---

# 17. Development Philosophy

VoltEngine is being developed incrementally.

The goal is not to reproduce a large existing machine-learning framework feature-for-feature.

The goal is to understand and implement the fundamental components required to build small AI systems in C++.

The development order should therefore prioritize:

```text
Foundation
   ↓
Tensor operations
   ↓
Neural-network layers
   ↓
Forward pass
   ↓
Loss
   ↓
Backpropagation
   ↓
Optimizer
   ↓
Training
   ↓
Model serialization
   ↓
Performance optimization
   ↓
GPU acceleration
   ↓
Larger models
```

This order keeps the framework understandable and gives each layer of the system a stable foundation before more complex functionality is added.

---

# 18. Current API Summary

| Component | Function | Status |
|---|---|---|
| BPETokenizer | `BPETokenizer()` | Implemented |
| BPETokenizer | `token_train()` | Implemented / Development |
| BPETokenizer | `encode()` | Implemented |
| BPETokenizer | `decode()` | Implemented |
| BPETokenizer | `save_vocab()` | Implemented |
| BPETokenizer | `load_vocab()` | Planned |
| Activation | `sigmoid()` | Implemented |
| Activation | `softmax()` | Implemented |
| Neural Network | `Linear` | Planned |
| Tensor | Tensor operations | In Development |
| Training | Backpropagation | Planned |
| Training | Optimizers | Planned |
| Runtime | GPU acceleration | Planned |
| Generation | Video generation | Long-Term |

---

**VoltEngine Design & API Documentation — v1.0.0**
