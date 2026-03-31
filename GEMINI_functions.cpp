#include "functions.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

void find_target_cities(const std::string& file_name, int k, int l) {
  std::ifstream file(file_name);
  if (!file.is_open()) {
    std::cerr << "Ошибка: файл не найден!" << std::endl;
    return;
  }

  int n;
  if (!(file >> n)) return;

  // Считываем матрицу смежности.
  std::vector<std::vector<int>> adj(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      file >> adj[i][j];
    }
  }
  file.close();

  // BFS для поиска кратчайших путей. -1 означает, что город не посещен.
  std::vector<int> dist(n, -1);
  std::queue<int> q;

  // Города в задаче нумеруются с 1.
  int start_node = k - 1;
  if (start_node < 0 || start_node >= n) return;

  dist[start_node] = 0;
  q.push(start_node);

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

  // Собираем города, где количество пересадок (дистанция - 1) >= l.
  std::vector<int> result;
  for (int i = 0; i < n; ++i) {
    if (dist[i] > 0 && (dist[i] - 1) >= l) {
      result.push_back(i + 1);
    }
  }

  // Вывод результата.
  if (result.empty()) {
    std::cout << -1 << std::endl;
  } else {
    std::sort(result.begin(), result.end());
    for (size_t i = 0; i < result.size(); ++i) {
      std::cout << result[i] << (i == result.size() - 1 ? "" : " ");
    }
    std::cout << std::endl;
  }
}
