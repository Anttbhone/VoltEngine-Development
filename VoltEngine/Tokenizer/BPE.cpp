#include "BPE.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>

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
std::string BPETokenizer::decode(const std::vector<int>& input_ids) {
    std::string result_text = "";
    for (int id : input_ids) {
        result_text += inverse_vocab[id];
    }
    return result_text;
}
void BPETokenizer::token_train(int target_vocab_size) {
    while (vocab.size() < target_vocab_size) {
    }
}