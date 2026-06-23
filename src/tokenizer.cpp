#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>

int main() {
    std::vector<std::string> test = {"A", "N", "T", "T", "</w>"};
    std::map<std::pair<std::string, std::string>, int> pair_counts;
    
    // 1. Fix the loop declaration and stop ONE element early (- 1)
    for (int i = 0; i < test.size() - 1; i++) {
        
        // 2. Add your boundary condition first using test[i]
        if (test[i] == "</w>") {
            continue;
        }
        
        // 3. Create your pair from test[i] and test[i+1]
        std::pair<std::string, std::string> current_pair = {test[i], test[i+1]};
        
        // 4. Increment the value inside the map
        pair_counts[current_pair]++;
    }
    
    return 0;
}
