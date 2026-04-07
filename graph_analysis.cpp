#include "graph_analysis.h"
#include <fstream>
#include <iostream>
#include <queue>

GraphAnalyzer::GraphAnalyzer(int city_count)
    : city_count_(city_count),
    adjacency_matrix_(city_count, std::vector<int>(city_count, 0)) {
}

void GraphAnalyzer::load_adjacency_matrix_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    for (int i = 0; i < city_count_; ++i) {
        for (int j = 0; j < city_count_; ++j) {
            file >> adjacency_matrix_[i][j];
        }
    }
    file.close();
}

std::vector<int> GraphAnalyzer::bfs_with_transfers(int start) {
    std::vector<int> distances(city_count_, -1);
    std::queue<std::pair<int, int>> queue;  // {city, transfer_count}
    queue.push({ start, 0 });
    distances[start] = 0;

    while (!queue.empty()) {
        std::pair<int, int> current_pair = queue.front();
        int current_city = current_pair.first;
        int current_transfers = current_pair.second;
        queue.pop();

        for (int neighbor = 0; neighbor < city_count_; ++neighbor) {
            if (adjacency_matrix_[current_city][neighbor] == 1 &&
                distances[neighbor] == -1) {
                distances[neighbor] = current_transfers + 1;
                queue.push({ neighbor, current_transfers + 1 });
            }
        }
    }
    return distances;
}

std::vector<int> GraphAnalyzer::find_cities_with_min_transfers(
    int start_city, int min_transfers) {
    std::vector<int> distances = bfs_with_transfers(start_city);
    std::vector<int> result;

    for (int city = 0; city < city_count_; ++city) {
        if (distances[city] >= min_transfers) {
            result.push_back(city + 1);  // Нумерация с 1
        }
    }

    if (result.empty()) {
        result.push_back(-1);
    }
    return result;
}
