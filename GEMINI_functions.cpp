#include "functions.h"
#include <iostream>
#include <algorithm>
#include <random>

void runShuffleProcess(const std::wstring& original) {
    std::wstring current = original;
    int attempts = 0;

    std::random_device rd;
    std::mt19937 g(rd());

    do {
        std::shuffle(current.begin(), current.end(), g);
        // Âûâîä øèðîêîé ñòðîêè
        std::wcout << current << std::endl;
        attempts++;
    } while (current != original);

    std::wcout << L"Ïîïûòîê: " << attempts << std::endl;
}
