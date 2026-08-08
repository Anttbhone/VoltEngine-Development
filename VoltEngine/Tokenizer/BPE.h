#pragma once
#include <string>
#include <vector>
#include <map>

class BPETokenizer {
public:
    std::map<std::string, int> vocabs;
    std::map<int, std::string> inverse_vocabs;
    int next_token_id;

    BPETokenizer();
    std::vector<int> encode(const std::string& text);
    std::string decode(const std::vector<int>& input_ids);
};
