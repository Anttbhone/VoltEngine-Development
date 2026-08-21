#include "BPE.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>

BPETokenizer::BPETokenizer() : next_token_id(259) {
    vocab["<PAD>"] = 256; inverse_vocab[256] = "<PAD>";
    vocab["<BOS>"] = 257; inverse_vocab[257] = "<BOS>";
    vocab["<EOS>"] = 258; inverse_vocab[258] = "<EOS>";
    
    for (int i = 0; i < 256; i++) {
        std::string byte_str(1, static_cast<char>(i));
        vocab[byte_str] = i;
        inverse_vocab[i] = byte_str;
    }
}

std::vector<int> BPETokenizer::encode(const std::string& text) {
    std::vector<int> compressed_tokens;
    size_t i = 0;
    while (i < text.length()) {
        int longest_match_id = -1;
        size_t longest_match_len = 0;
        
        for (auto const& item : vocab) { 
            std::string token_string = item.first;
            if (i + token_string.length() <= text.length()) {
                if (text.substr(i, token_string.length()) == token_string) {
                    if (token_string.length() > longest_match_len) {
                        longest_match_len = token_string.length();
                        longest_match_id = item.second;
                    }
                }
            }
        }
        if (longest_match_len > 0) {
            compressed_tokens.push_back(longest_match_id);
            i += longest_match_len;
        } else {
            compressed_tokens.push_back(static_cast<unsigned char>(text[i]));
            i++;
        }
    }
    return compressed_tokens;
}
/*--------------------------------------------------------------------------------------------------------*/
std::string BPETokenizer::decode(const std::vector<int>& input_ids) {
    std::string result_text = "";
    for (int id : input_ids) {
        result_text += inverse_vocab[id];
    }
    return result_text;
}
/*--------------------------------------------------------------------------------------------------------*/
void BPETokenizer::token_train(int target_vocab_size, const std::string& dataset) {
    std::ifstream dataset_file(dataset, std::ios::binary);
    std::vector<int> tokens;
    char byte;
    while (dataset_file.get(byte)) {
        tokens.push_back(static_cast<unsigned char>(byte));
    }
    while (vocab.size() < target_vocab_size) {
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
        std::string new_token_str = inverse_vocab[best_pair.first] + inverse_vocab[best_pair.second];
        vocab[new_token_str] = next_token_id;
        inverse_vocab[next_token_id] = new_token_str;
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
    dataset_file.close();
}
/*---------------------------------------------------------------------------------------------*/
void BPETokenizer::save_vocab(const std::string& filepath) {
    std::ofstream out_file(filepath);
    for (auto const& item : vocab) {
        std::string token_text = item.first;
        if (token_text == "\n") token_text = "\\n";
        if (token_text == "\r") token_text = "\\r";
        out_file << item.second << " " << token_text << "\n";
    }
    out_file.close();
}
/*------------------------------------------------------------------------------------------------------*/
void BPETokenizer::load_vocab(const std::string& filepath) {
    std::ifstream in_path(filepath);
    int id;
    std::string token_text;
    while (in_path >> id >> token_text) {
        vocab[token_text] = id;
        inverse_vocab[id] = token_text;
    }
}