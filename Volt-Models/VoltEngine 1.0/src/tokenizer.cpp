#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

std::string decode(const std::vector<int>& input_ids, std::map<int, std::string>& inverse_map) {
    std::string result_text;
    for (int id : input_ids) {
        result_text += inverse_map[id];
    }
    return result_text;
}

int main() {
    std::ifstream dataset("dataset.txt", std::ios::binary);
    std::vector<int> tokens;
    char byte;
    while (dataset.get(byte)) {
        tokens.push_back(static_cast<unsigned char>(byte));
    }
    std::map<std::string, int> vocabs;
    std::map<int, std::string> inverse_vocabs;
    int next_token_id = 259;
    vocabs["<PAD>"] = 256; inverse_vocabs[256] = "<PAD>";
    vocabs["<BOS>"] = 257; inverse_vocabs[257] = "<BOS>";
    vocabs["<EOS>"] = 258; inverse_vocabs[258] = "<EOS>";
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
                max_count = item.second.size();
            }
        }
        if (max_count <= 1) break;
        std::string new_token_str = inverse_vocabs[best_pair.first] + inverse_vocabs[best_pair.second];
        vocabs[new_token_str] = next_token_id;
        inverse_vocabs[next_token_id] = new_token_str;
        std::cout << "Merged ID (" << best_pair.first << ", " << best_pair.second << ") ID -> " << next_token_id << "\n";

        const std::vector<size_t>& positions = pair_position[best_pair];
        for (size_t pos : positions) {
            if (pos + 1 < tokens.size()) {
                if (tokens[pos] == best_pair.first && tokens[pos + 1] == best_pair.second) {
                    tokens[pos] = next_token_id;
                    tokens[pos + 1] = -1; 
                }
            }
        }
        next_token_id++;
        size_t write_idx = 0;
        for (int read_idx = 0; read_idx < tokens.size(); ++read_idx) {
            if (tokens[read_idx] != -1) {
                tokens[write_idx] = tokens[read_idx];
                write_idx++;
                }
            }
            tokens.resize(write_idx);
        }
    std::ofstream out_file("vocab.model");
    for (auto const& item : vocabs) {
        std::string token_text = item.first;
        if (token_text == "\n") token_text = "\\n";
        if (token_text == "\r") token_text = "\\r";
        out_file << item.second << " " << token_text << "\n";
    }
    std::string final_output = decode(tokens, inverse_vocabs);
    std::cout << "Docoded Text: " << final_output << "\n";
    out_file.close();
    dataset.close();
    return 0;
}