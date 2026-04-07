#ifndef GRAPH_ANALYSIS_H
#define GRAPH_ANALYSIS_H

#include <vector>
#include <string>

class GraphAnalyzer {
public:
	explicit GraphAnalyzer(int city_count);
	void load_adjacency_matrix_from_file(const std::string& filename);
	std::vector<int> find_cities_with_min_transfers(int start_city, int min_transfers);

private:
	int city_count_;
	std::vector<std::vector<int>> adjacency_matrix_;
	std::vector<int> bfs_with_transfers(int start);
};

#endif  // GRAPH_ANALYSIS_H
