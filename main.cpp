#include "word_shuffler.h"

#include <iostream>
#include <string>

int main() {
    setlocale(LC_ALL, "RU");
    std::string input_word;

    std::cout << "Введите слово: ";
    std::getline(std::cin, input_word);

    // Проверяем, что слово не пустое
    if (input_word.empty()) {
        std::cerr << "Ошибка: введено пустое слово!" << std::endl;
        return 1;
    }

    // Создаем объект для перемешивания
    WordShuffler shuffler(input_word);

    // Запускаем процесс перестановок
    int attempts = shuffler.ShuffleUntilMatch();

    // Выводим результат
    std::cout << attempts << " попыток" << std::endl;

    return 0;
}