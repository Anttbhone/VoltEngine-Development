#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

int main() {
    std::ifstream dataset("dataset.txt", std::ios::binary);
    std::vector<int> tokens;
    char byte;
    while (dataset.get(byte)) {
        tokens.push_back(static_cast<unsigned char>(byte));
    }
    std::map<std::string, int> vocabs;
    std::map<int, std::string> inverse_vocabs;
    int next_token_id = 256;
    for (int i = 0; i < 256; i++) {
        std::string byte_str(1, static_cast<char>(i));
        vocabs[byte_str] = i;
        inverse_vocabs[i] = byte_str;
    }
    while (vocabs.size() < 300) {
        std::map<std::pair<int, int> , std::vector<size_t>> pair_position;
        for (size_t i = 0; i < tokens.size() - 1; ++i) {
            std::pair<int, int> current_pair{tokens[i], tokens[i + 1]};
            pair_position[current_pair].push_back(i);
            
        }
        std::pair<int, int> best_pair{-1, -1};
        size_t max_count = 0;
        for (auto const& item : pair_position) {
            if (item.second.size() > max_count) {
                best_pair = item.first;
                max_count.item.second.size();
            }
        }
        if (max_count <= 1) break;
    }
    dataset.close();
    return 0;
}