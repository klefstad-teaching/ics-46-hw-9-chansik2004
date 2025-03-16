#include "ladder.h"

int main() {
    std::set<std::string> word_list;
    load_words(word_list, "words.txt");

    std::string begin_word, end_word;
    std::cout << "Enter the start word: ";
    std::cin >> begin_word;
    std::cout << "Enter the end word: ";
    std::cin >> end_word;

    std::vector<std::string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    print_word_ladder(ladder);
}
