#include "ladder.h"

void error(std::string word1, std::string word2, std::string msg) {
    std::cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << std::endl;
}

bool edit_distance_within(const std::string & str1, const std::string & str2, int d) {
    int len_str1 = str1.size(), len_str2 = str2.size();
    if (abs(len_str1 - len_str2) > 1) {
        return false;
    }
    int diff_count = 0;
    for (size_t i = 0, j = 0; i < len_str1 && j < len_str2; i++, j++) {
        if (str1[i] != str2[j]) {
            diff_count++;
            if (len_str1 > len_str2) {
                j--;
            } else if (len_str1 < len_str2) {
                i--;
            }
        }
        if (diff_count > d) {
            return false;
        }
    }
    return true;
}
