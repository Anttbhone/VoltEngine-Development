#pragma once
#include <string>
#include <vector>
#include <map>

class BPETokenizer {
public:
    std::map<int, std::string> inverse_vocab;
    std::map<std::string, int> vocab;
    int next_token_id;
    int target_vocab;
    BPETokenizer();
    std::vector<int> encode(const std::string& text);
    std::string decode(const std::vector<int>& input_ids);
    void token_train;
    int target_vocab_size
};
