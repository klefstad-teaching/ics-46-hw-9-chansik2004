#include "ladder.h"

void error(std::string word1, std::string word2, std::string msg) {
    std::cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << std::endl;
}
