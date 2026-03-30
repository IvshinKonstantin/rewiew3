#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include "functions.h"

int main() {
    // Настройка консоли для вывода UTF-16 (лучший способ для Windows/Visual Studio)
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    std::wstring inputWord;
    std::wcout << L"Введите слово: ";
    std::wcin >> inputWord;

    runShuffleProcess(inputWord);

    return 0;
}
