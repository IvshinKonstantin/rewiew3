#ifndef WORD_SHUFFLER_H_
#define WORD_SHUFFLER_H_

#include <string>

// Класс для перемешивания букв в слове
class WordShuffler {
public:
	// Конструктор, принимающий исходное слово
	explicit WordShuffler(const std::string& original_word);

	// Запускает процесс перемешивания до совпадения с исходным словом
	// Возвращает количество попыток
	int shuffle_until_match();

private:
	std::string original_word_;
	std::string current_word_;
};

#endif  // WORD_SHUFFLER_H_
