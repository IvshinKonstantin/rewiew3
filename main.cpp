#include <iostream>
#include <string>
#include "word_shuffler.h"

int main() {
    std::string input_word;
    std::cout << "¬ведите слово: ";
    std::cin >> input_word;

    if (input_word.empty()) {
        std::cerr << "ќшибка: введено пустое слово." << std::endl;
        return 1;
    }

    WordShuffler shuffler(input_word);
    int attempts = shuffler.shuffle_until_match();

    std::cout << attempts << " попыток" << std::endl;
    return 0;
}
