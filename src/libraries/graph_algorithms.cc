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

int GraphAlgorithms::GetShortestPathBetweenVertices(const Graph& graph,
                                                    int vertex1, int vertex2) {
  const size_t size = graph.Size();
  if (size == 0 || vertex1 < 1 || vertex2 < 1 ||
      static_cast<size_t>(vertex1) > size ||
      static_cast<size_t>(vertex2) > size) {
    return -1;
  }

  using Distance = long long;
  const Distance INF = 1e18;

  const auto& matrix = graph.GetAdjecencyMatrix();

  const int start = vertex1 - 1;
  const int finish = vertex2 - 1;

  /* trying to prevent possible overflow */
  std::vector<Distance> distance(size, INF);
  std::vector<bool> visited(size, false);

  distance[start] = 0;

  for (size_t i = 0; i < size; ++i) {
    int v = -1;
    for (size_t j = 0; j < size; ++j) {
      if (!visited[j] && (v == -1 || distance[j] < distance[v])) {
        v = static_cast<int>(j);
      }
    }
    if (v == -1 || distance[v] == INF) break;

    visited[v] = true;

    for (size_t u = 0; u < size; ++u) {
      if (!visited[u] && matrix[v][u] > 0) {
        distance[u] = std::min(distance[v] + matrix[v][u], distance[u]);
      }
    }
  }
  if (distance[finish] > std::numeric_limits<int>::max()) {
    return -1;
  }
  return (distance[finish] == INF) ? -1 : distance[finish];
}

std::vector<std::vector<int>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(const Graph& graph) {
  
}