#include "word_shuffler.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

WordShuffler::WordShuffler(const std::string& word)
    : original_word_(word), current_word_(word) {
    // »нициализируем генератор случайных чисел
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

int WordShuffler::ShuffleUntilMatch() {
    int attempt_count = 0;

    // »спользуем do-while дл€ гарантированного выполнени€ хот€ бы одной
    // перестановки
    do {
        ShuffleWord();
        PrintCurrentWord();
        ++attempt_count;
    } while (!IsMatched());

    return attempt_count;
}

void WordShuffler::ShuffleWord() {
    // —оздаем временную копию дл€ перемешивани€
    std::string temp = current_word_;

    // »спользуем алгоритм случайного перемешивани€
    // ѕроходим по всем позици€м слова, начина€ с конца
    for (size_t i = temp.length() - 1; i > 0; --i) {
        // ¬ыбираем случайную позицию от 0 до i
        size_t j = std::rand() % (i + 1);
        // ћен€ем местами элементы на позици€х i и j
        std::swap(temp[i], temp[j]);
    }

    current_word_ = temp;
}

bool WordShuffler::IsMatched() const {
    return current_word_ == original_word_;
}

void WordShuffler::PrintCurrentWord() const {
    std::cout << current_word_ << std::endl;
}