#include <iostream>
#include <string>
#include "functions.h"

int main() {
    setlocale(LC_ALL, "Russian");

    std::string fileName;
    int K, L;

    std::cout << "¬ведите им€ файла: ";
    std::cin >> fileName;
    std::cout << "¬ведите номер начального города K: ";
    std::cin >> K;
    std::cout << "¬ведите минимальное количество пересадок L: ";
    std::cin >> L;

    findTargetCities(fileName, K, L);

    return 0;
}
