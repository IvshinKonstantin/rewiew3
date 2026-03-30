#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include "functions.h"

int main() {
    // Íàñòðîéêà êîíñîëè äëÿ âûâîäà UTF-16 (ëó÷øèé ñïîñîá äëÿ Windows/Visual Studio)
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    std::wstring inputWord;
    std::wcout << L"Ââåäèòå ñëîâî: ";
    std::wcin >> inputWord;

    runShuffleProcess(inputWord);

    return 0;
}
