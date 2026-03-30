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
        // Вывод широкой строки
        std::wcout << current << std::endl;
        attempts++;
    } while (current != original);

    std::wcout << L"Попыток: " << attempts << std::endl;
}
