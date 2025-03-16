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
                visited.insert(word);
                std::vector<std::string> new_ladder = ladder;
                new_ladder.push_back(word);

                if (word == end_word) {
                    return new_ladder;
                }

                ladder_queue.push(new_ladder);
            }
        }
    }
    error(begin_word, end_word, "No ladder found");
    return {};
}

void load_words(std::set<std::string> & word_list, const std::string & file_name) {
    std::ifstream in(file_name);
    if (!in) {
        std::cerr << "Error: Unable to open " << file_name << std::endl;
        return;
    }
    std::string word;
    while (in >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const std::vector<std::string> & ladder) {
    if (ladder.empty()) {
        std::cerr << "Error: No ladder found" << std::endl;
        return;
    }
    for (size_t i = 0; i < ladder.size(); ++i) {
        std::cout << ladder[i];
        if (i != ladder.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

void verify_word_ladder() {
    std::set<std::string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
