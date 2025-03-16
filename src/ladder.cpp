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

bool is_adjacent(const std::string & word1, const std::string & word2) {
    return edit_distance_within(word1, word2, 1);
}

std::vector<std::string> generate_word_ladder(const std::string & begin_word, const std::string & end_word, const std::set<std::string> & word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "Start and End words cannot be same");
        return {};
    }

    std::queue<std::vector<std::string>> ladder_queue;
    ladder_queue.push({begin_word});
    std::set<std::string> visited;
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        std::vector<std::string> ladder = ladder_queue.front();
        ladder_queue.pop();
        std::string last_word = ladder.back();

        for (const std::string & word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                std::vector<std::string> new_ladder = ladder;
                new_ladder.push_back(word);

                if (word == end_word) {
                    return new_ladder;
                }

                visited.insert(word);
                ladder_queue.push(new_ladder);
            }
        }
    }
    error(begin_word, end_word, "No ladder found");
    return {};
}
