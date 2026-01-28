#ifndef S21_GRAPH_ALGORITHMS_H_
#define S21_GRAPH_ALGORITHMS_H_

#include <vector>

#include "graph.h"
#include "s21_containers.h"

class GraphAlgorithms {
 public:
  static std::vector<int> DepthFirstSearch(const Graph& graph,
                                           int start_vertex);
  static std::vector<int> BreadthFirstSearch(const Graph& graph,
                                             int start_vertex);
};

#endif  // S21_GRAPH_ALGORITHMS_H_