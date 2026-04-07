#include "graph.h"
#include <fstream>
#include <queue>
#include <algorithm>
#include <stdexcept>
#include <limits>

//FIX_ME: Constructor lacked exception handling and proper file validation
// Old code: No constructor implementation
FlightGraph::FlightGraph(const std::string& filename) : n_(0) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    file >> n_;
    if (n_ <= 0 || n_ > 15) {
        throw std::runtime_error("Invalid number of cities (must be 1-15)");
    }

    adjacency_matrix_.resize(n_, std::vector<int>(n_, 0));

    for (int i = 0; i < n_; ++i) {
        for (int j = 0; j < n_; ++j) {
            file >> adjacency_matrix_[i][j];
            // Validate matrix entries
            if (adjacency_matrix_[i][j] != 0 && adjacency_matrix_[i][j] != 1) {
                throw std::runtime_error("Invalid matrix entry at position (" +
                    std::to_string(i) + "," + std::to_string(j) + ")");
            }
        }
    }
}

//FIX_ME: BFS implementation was missing
// Old code: No BFS implementation
std::vector<int> FlightGraph::BFSShortestPaths(int start) const {
    const int kInfinity = std::numeric_limits<int>::max();
    std::vector<int> distances(n_, kInfinity);
    std::queue<int> bfs_queue;

    // Convert to 0-based indexing
    int start_index = start - 1;
    distances[start_index] = 0;
    bfs_queue.push(start_index);

    while (!bfs_queue.empty()) {
        int current = bfs_queue.front();
        bfs_queue.pop();

        for (int neighbor = 0; neighbor < n_; ++neighbor) {
            if (adjacency_matrix_[current][neighbor] == 1 &&
                distances[neighbor] == kInfinity) {
                distances[neighbor] = distances[current] + 1;
                bfs_queue.push(neighbor);
            }
        }
    }

    return distances;
}

//FIX_ME: Method didn't correctly handle layover count logic
// Old code: No implementation
std::vector<int> FlightGraph::FindCitiesWithExactLayovers(int k, int l) const {
    // Validate input
    if (k < 1 || k > n_) {
        throw std::out_of_range("City number K is out of range");
    }

    if (l < 0) {
        throw std::invalid_argument("Number of layovers cannot be negative");
    }

    std::vector<int> shortest_paths = BFSShortestPaths(k);
    std::vector<int> result;

    // A layover is a stop between flights
    // Number of layovers = number of edges - 1
    // If distance in edges = d, then layovers = d - 1
    // We need exactly L layovers, so distance = L + 1
    int target_distance = l + 1;

    // Convert to 1-based indexing for result
    for (int city = 0; city < n_; ++city) {
        int city_number = city + 1;
        // Skip the starting city itself
        if (city_number == k) {
            continue;
        }

        // Check if shortest path has exactly target_distance edges
        if (shortest_paths[city] == target_distance) {
            result.push_back(city_number);
        }
    }

    std::sort(result.begin(), result.end());
    return result;
}