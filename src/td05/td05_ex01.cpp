#include <vector>
#include <algorithm>
#include <iostream>

size_t folding_string_hash(std::string const& s, size_t max) {
    size_t total = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        total += int(s[i]);
        total = total % max;
    }
    return total;
    
}

size_t folding_string_ordered_hash(std::string const& s, size_t max) {
    size_t total = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        total += (int(s[i]) * (i + 1));
        total = total % max;
    }
    return total;
    
}





int main() {
    std::cout << folding_string_ordered_hash("coucou", 5000) << std::endl;
}
