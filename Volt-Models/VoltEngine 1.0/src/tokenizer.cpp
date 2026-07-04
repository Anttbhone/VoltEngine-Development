#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

int main(){

    // Load the dataset in binary and check if dataset exsits
    std::ifstream dataset("dataset.txt", std::ios::binary);
    if (!dataset.is_open()) {
        std::cout << "Error: dataset not found!";
        return 1;
    }

    // Convert signed char to unsigned int (0 - 255)
    std::vector<int> tokens;
    char byte;
    while (dataset.get(byte)) {
        tokens.push_back(static_cast<unsigned char>(byte));
    }
    dataset.close();
    std::cout << "Loaded " << tokens.size() << " Bytes in total!";
    
    // Set up maps of vocab
    std::map<std::string, int> vocab;
    std::map<int, std::string> inverse_vocab;
    int next_token_id = 256; // 0 - 255 is for bytes

    // Pre-assign vocab with bytes (0 - 255)
    for (int i = 0; i < 256; ++i) {
        std::string byte_str(1, static_cast<char>(i));
        vocab[byte_str] = i;
        inverse_vocab[i] = byte_str;
    }

    // Setting up target vocab size
    int target_vocab_size = 300;

    // Main BPE loop
    
    return 0;
}