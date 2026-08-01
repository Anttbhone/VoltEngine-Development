#pragma once
#include <string>
#include <map>
#include <vector>

class BPETokenizer {
public:
    std::map<int, std::string> vocabs;
    std::map<std::string, int> inverse_vocabs;
    int next_token_id;
    BPETokenizer();
    std::vector<int> encode(const std::string& text);
    std::string decode(const std::vector<int>& input_ids);
};
