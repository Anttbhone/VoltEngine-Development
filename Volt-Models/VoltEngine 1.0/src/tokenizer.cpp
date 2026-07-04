#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

int main() {
    // 1. Load the dataset file raw byte by byte
    std::ifstream file("dataset.txt", std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error: Cannot open dataset.txt\n";
        return 1;
    }

    std::vector<int> tokens;
    char byte;
    while (file.get(byte)) {
        tokens.push_back(static_cast<unsigned char>(byte));
    }
    file.close();
    std::cout << "Loaded " << tokens.size() << " bytes.\n";

    // 2. Setup Vocabulary maps
    std::map<std::string, int> vocab;
    std::map<int, std::string> inverse_vocab;
    int next_token_id = 256; 

    for (int i = 0; i < 256; ++i) {
        std::string byte_str(1, static_cast<char>(i));
        vocab[byte_str] = i;
        inverse_vocab[i] = byte_str;
    }

    int target_vocab_size = 300; 

    // 3. Fast Main BPE Loop
    while (vocab.size() < target_vocab_size) {
        // Maps a token pair to all index positions where it appears
        std::map<std::pair<int, int>, std::vector<size_t>> pair_positions;

        // Step A: Scan once to map out pair positions
        size_t i = 0;
        while (i < tokens.size() - 1) {
            std::pair<int, int> current_pair = {tokens[i], tokens[i+1]};
            pair_positions[current_pair].push_back(i);
            i++;
        }

        // Step B: Instantly find the pair with the most occurrences 
        std::pair<int, int> best_pair = {-1, -1};
        size_t max_count = 0;
        for (auto const& item : pair_positions) {
            if (item.second.size() > max_count) {
                max_count = item.second.size();
                best_pair = item.first;
            }
        }

        if (max_count <= 1) break; // Stop if no pairs repeat

        // Step C: Register the newly merged pair
        std::string merged_string = inverse_vocab[best_pair.first] + inverse_vocab[best_pair.second];
        vocab[merged_string] = next_token_id;
        inverse_vocab[next_token_id] = merged_string;

        std::cout << "Merged ID (" << best_pair.first << ", " << best_pair.second 
                  << ") -> ID " << next_token_id << " (Seen " << max_count << " times)\n";

        // Step D: IN-PLACE INLINE MERGING (No new vector creation, no massive copying)
        // We overwrite items directly inside the original array and use a flag to hide deleted slots
        const std::vector<size_t>& positions = pair_positions[best_pair];
        
        for (size_t pos : positions) {
            // Check if the pair has already been disrupted by a previous adjacent merge
            if (tokens[pos] == best_pair.first && tokens[pos+1] == best_pair.second) {
                tokens[pos] = next_token_id; // Overwrite left token with the new ID
                tokens[pos+1] = -1;          // Mark right token as -1 (soft deleted)
            }
        }

        // Step E: Fast clean up of the -1 gaps (Only done once per entire merge round)
        size_t write_idx = 0;
        for (size_t read_idx = 0; read_idx < tokens.size(); ++read_idx) {
            if (tokens[read_idx] != -1) {
                tokens[write_idx] = tokens[read_idx];
                write_idx++;
            }
        }
        tokens.resize(write_idx); // Instantly trims off dead allocation space at the end

        next_token_id++;
    }

    // 4. Save the trained rules to disk
    std::ofstream out("vocab.model");
    for (auto const& item : vocab) {
        std::string token_text = item.first;
        if (token_text == "\n") token_text = "\\n";
        if (token_text == "\r") token_text = "\\r";
        out << item.second << " " << token_text << "\n";
    }
    out.close();
    std::cout << "Successfully saved vocabulary file to vocab.model\n";

    return 0;
}
