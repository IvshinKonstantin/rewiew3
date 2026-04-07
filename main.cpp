#include "graph_analysis.h"
#include <iostream>
#include <vector>
#include <string>  // Для работы со std::string

int main() {
    int city_count, start_city, min_transfers;
    std::string filename;  // Переменная для хранения имени файла

    // Запрос количества городов
    std::cout << "Enter number of cities (n <= 15): ";
    std::cin >> city_count;

    // Запрос начального города
    std::cout << "Enter start city (K): ";
    std::cin >> start_city;

    // Запрос минимального числа пересадок
    std::cout << "Enter minimum number of transfers (L): ";
    std::cin >> min_transfers;

    // Запрос имени файла с матрицей смежности
    std::cout << "Enter the filename with adjacency matrix: ";
    std::cin >> filename;  // Ввод имени файла с консоли

    GraphAnalyzer analyzer(city_count);
    analyzer.load_adjacency_matrix_from_file(filename);  // Используем введённое имя файла

    std::vector<int> result = analyzer.find_cities_with_min_transfers(
        start_city - 1, min_transfers);  // Вычитаем 1 для индексации с 0

    // Вывод результата
    for (int city : result) {
        std::cout << city << " ";
    }
    std::cout << std::endl;

    return 0;
}
