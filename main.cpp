#include "graph.h"
#include <iostream>
#include <vector>

int main() {
    std::string filename;
    int k, l;

    std::cout << "Enter filename: ";
    std::cin >> filename;

    std::cout << "Enter starting city K (1-based index): ";
    std::cin >> k;

    std::cout << "Enter minimum number of layovers L: ";
    std::cin >> l;

    try {
        FlightGraph graph(filename);

        std::vector<int> result = graph.FindCitiesWithExactLayovers(k, l);

        if (result.empty()) {
            std::cout << -1 << std::endl;
        }
        else {
            for (size_t i = 0; i < result.size(); ++i) {
                std::cout << result[i];
                if (i < result.size() - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}