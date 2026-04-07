#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <string>

class FlightGraph {
public:
	// Constructor that reads graph from file
	explicit FlightGraph(const std::string& filename);

	// Finds cities reachable from city K with exactly L layovers
	// and no shorter paths exist
	std::vector<int> FindCitiesWithExactLayovers(int k, int l) const;

	// Returns number of cities
	int GetCityCount() const { return n_; }

private:
	int n_;  // Number of cities
	std::vector<std::vector<int>> adjacency_matrix_;

	// Breadth-First Search to find shortest paths from start city
	std::vector<int> BFSShortestPaths(int start) const;
};

#endif  // GRAPH_H_