#include "functions.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

void findTargetCities(const std::string& fileName, int K, int L) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Ошибка: файл не найден!" << std::endl;
        return;
    }

    int n;
    file >> n;

    // Считываем матрицу смежности
    std::vector<std::vector<int>> adj(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> adj[i][j];
        }
    }
    file.close();

    // Алгоритм BFS для поиска кратчайших путей от города K
    // Дистанция -1 означает, что город еще не посещен
    std::vector<int> dist(n, -1);
    std::queue<int> q;

    // Города нумеруются с 1, поэтому вычитаем 1 для индекса вектора
    int startNode = K - 1;
    dist[startNode] = 0;
    q.push(startNode);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; ++v) {
            if (adj[u][v] == 1 && dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    // Собираем города, до которых кратчайший путь >= L + 1 (т.е. пересадок >= L)
    std::vector<int> result;
    for (int i = 0; i < n; ++i) {
        // Условие: путь существует (dist != -1), это не сам город K (dist > 0),
        // и количество пересадок (dist-1) >= L
        if (dist[i] != -1 && dist[i] > 0 && (dist[i] - 1) >= L) {
            result.push_back(i + 1); // Возвращаем к нумерации с 1
        }
    }

    // Вывод результата
    if (result.empty()) {
        std::cout << -1 << std::endl;
    }
    else {
        std::sort(result.begin(), result.end());
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i] << (i == result.size() - 1 ? "" : " ");
        }
        std::cout << std::endl;
    }
}
