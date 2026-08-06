# 1. Compiler selection and the production optimization speed flag
CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17

# 2. Track all implementation files across your VoltEngine directory tree
SRCS = main.cpp \
       VoltEngine/Core/Tensor.cpp \
       VoltEngine/NeuralNetwork/Activations.cpp \
       VoltEngine/Tokenizer/BPE.cpp

# 3. Name your output file executable
TARGET = volt_app

# 4. The main build rule execution pattern
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# 5. Clean rule to instantly sweep away compiled binaries safely
clean:
	rm -f $(TARGET)
