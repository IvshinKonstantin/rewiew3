#include "word_shuffler.h"
#include <algorithm>
#include <iostream>
#include <random>

WordShuffler::WordShuffler(const std::string& original_word)
    : original_word_(original_word), current_word_(original_word) {}

int WordShuffler::shuffle_until_match() {
    // »нициализаци€ генератора случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());

    int attempt_count = 0;

    do {
        // ѕеремешиваем буквы в текущем слове
        std::shuffle(current_word_.begin(), current_word_.end(), gen);
        ++attempt_count;
        // ¬ыводим текущее состо€ние слова
        std::cout << current_word_ << std::endl;
    } while (current_word_ != original_word_);

    return attempt_count;
}
