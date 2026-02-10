#ifndef S21_GRAPH_ALGORITHMS_H_
#define S21_GRAPH_ALGORITHMS_H_

#include <vector>

#include "graph.h"
#include "s21_containers.h"
#include "tsp.h"

namespace s21 {

class GraphAlgorithms {
 public:
  static std::vector<int> DepthFirstSearch(const Graph& graph,
                                           int start_vertex);
  static std::vector<int> BreadthFirstSearch(const Graph& graph,
                                             int start_vertex);
  static int GetShortestPathBetweenVertices(const Graph& graph, int vertex1,
                                            int vertex2);
  static std::vector<std::vector<long long>> GetShortestPathsBetweenAllVertices(
      const Graph& graph);
  static std::vector<std::vector<long long>> GetLeastSpanningTree(
      const Graph& graph);
  static tsp::TsmResult SolveTravelingSalesmanProblem(const Graph& graph);

 private:
  static std::vector<std::vector<long long>> CreateMSTAdjacencyMatrix(
      size_t size, const std::vector<std::vector<int>>& matrix,
      const std::vector<int>& parent);
};

}  // namespace s21

#endif  // S21_GRAPH_ALGORITHMS_H_