#ifndef WORD_SHUFFLER_H
#define WORD_SHUFFLER_H

#include <string>

//  ласс дл€ перемешивани€ букв в слове
class WordShuffler {
public:
	//  онструктор принимает исходное слово
	explicit WordShuffler(const std::string& word);

	// «апускает процесс перестановок до совпадени€ с исходным словом
	// ¬озвращает количество выполненных перестановок
	int ShuffleUntilMatch();

	// ¬ыводит текущее слово
	void PrintCurrentWord() const;

private:
	std::string original_word_;  // »сходное слово
	std::string current_word_;   // “екущее слово после перестановок

	// ѕеремешивает буквы в слове случайным образом
	void ShuffleWord();

	// ѕровер€ет, совпадает ли текущее слово с исходным
	bool IsMatched() const;
};

#endif  // WORD_SHUFFLER_H