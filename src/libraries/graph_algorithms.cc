#include "graph_algorithms.h"

std::vector<int> GraphAlgorithms::DepthFirstSearch(const Graph& graph,
                                                   int start_vertex) {
  std::vector<int> result;
  const size_t size = graph.Size();
  if (size == 0 || start_vertex < 1 ||
      static_cast<size_t>(start_vertex) > size) {
    return result;
  }

  const auto& matrix = graph.GetAdjecencyMatrix();

  std::vector<bool> visited(size, false);
  s21::Stack<int> stack;

  const int start = start_vertex - 1;
  stack.push(start);

  /* DFS algorithm */
  while (!stack.empty()) {
    int v = stack.top();
    stack.pop();

    if (visited[v]) continue;
    visited[v] = true;

    result.push_back(v + 1);
    for (int u = static_cast<int>(size) - 1; u >= 0; --u) {
      if (matrix[v][u] != 0 && !visited[u]) {
        stack.push(u);
      }
    }
  }

  return result;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph& graph,
                                                     int start_vertex) {
  std::vector<int> result;
  const size_t size = graph.Size();
  if (size == 0 || start_vertex < 1 ||
      static_cast<size_t>(start_vertex) > size) {
    return result;
  }

  const auto& matrix = graph.GetAdjecencyMatrix();

  std::vector<bool> visited(size, false);
  s21::Queue<int> queue;

  const int start = start_vertex - 1;
  visited[start] = true;
  queue.push(start);

  /* BFS algorithm */
  while (!queue.empty()) {
    int v = queue.front();
    queue.pop();
    result.push_back(v + 1);

    for (size_t u = 0; u < size; ++u) {
      if (matrix[v][u] != 0 && !visited[u]) {
        visited[u] = true;
        queue.push(static_cast<int>(u));
      }
    }
  }

  return result;
}