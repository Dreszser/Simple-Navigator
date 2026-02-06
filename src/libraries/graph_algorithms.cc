#include "graph_algorithms.h"

std::vector<int> GraphAlgorithms::DepthFirstSearch(const Graph& graph,
                                                   int start_vertex) {
  std::vector<int> distance;
  const size_t size = graph.Size();
  if (size == 0 || start_vertex < 1 ||
      static_cast<size_t>(start_vertex) > size) {
    return distance;
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

    distance.push_back(v + 1);
    for (int u = static_cast<int>(size) - 1; u >= 0; --u) {
      if (matrix[v][u] != 0 && !visited[u]) {
        stack.push(u);
      }
    }
  }

  return distance;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph& graph,
                                                     int start_vertex) {
  std::vector<int> distance;
  const size_t size = graph.Size();
  if (size == 0 || start_vertex < 1 ||
      static_cast<size_t>(start_vertex) > size) {
    return distance;
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
    distance.push_back(v + 1);

    for (size_t u = 0; u < size; ++u) {
      if (matrix[v][u] != 0 && !visited[u]) {
        visited[u] = true;
        queue.push(static_cast<int>(u));
      }
    }
  }

  return distance;
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

  /* Dijkstra's algorithm */
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

std::vector<std::vector<long long>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(const Graph& graph) {
  const size_t size = graph.Size();

  using Distance = long long;
  const Distance INF = 1e18;

  if (size == 0) {
    return {};
  }

  std::vector<std::vector<Distance>> distance(size,
                                              std::vector<Distance>(size, INF));
  const auto& matrix = graph.GetAdjecencyMatrix();

  /* initialization of distance matrix */
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      if (i == j)
        distance[i][j] = 0;
      else if (matrix[i][j] > 0)
        distance[i][j] = matrix[i][j];
    }
  }
  /* Floyd-Warshall algorithm */
  for (size_t k = 0; k < size; ++k) {
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = 0; j < size; ++j) {
        if (distance[i][k] < INF && distance[k][j] < INF) {
          distance[i][j] =
              std::min(distance[i][j], distance[i][k] + distance[k][j]);
        }
      }
    }
  }
  /* cleaning up infinities */
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      if (distance[i][j] == INF) {
        distance[i][j] = 0;
      }
    }
  }
  return distance;
}

std::vector<std::vector<long long>> GraphAlgorithms::GetLeastSpanningTree(
    const Graph& graph) {
  const size_t size = graph.Size();

  using Distance = long long;
  const Distance INF = 1e18;

  if (size == 0) {
    return {};
  }

  const auto& matrix = graph.GetAdjecencyMatrix();

  std::vector<bool> visited(size, false);
  std::vector<Distance> dist(size, INF);
  std::vector<int> parent(size, -1);

  dist[0] = 0; /* starting from the first node */

  for (size_t n = 0; n < size; ++n) {
    int v = -1;
    /* looking for a node with the least distance */
    for (size_t i = 0; i < size; ++i) {
      if (!visited[i] && (v == -1 || dist[v] > dist[i])) {
        v = static_cast<int>(i);
      }
    }
    /* if the graph is disconnected */
    if (v == -1 || dist[v] == INF) {
      return {};
    }

    visited[v] = true;

    for (size_t u = 0; u < size; ++u) {
      if (!visited[u] && matrix[v][u] > 0 && matrix[v][u] < dist[u]) {
        dist[u] = matrix[v][u];
        parent[u] = v;
      }
    }
  }
  return CreateMSTAdjacencyMatrix(size, matrix, parent);
}

std::vector<std::vector<long long>> GraphAlgorithms::CreateMSTAdjacencyMatrix(
    size_t size, const std::vector<std::vector<int>>& matrix,
    const std::vector<int>& parent) {
  std::vector<std::vector<long long>> mst(size,
                                          std::vector<long long>(size, 0));
  for (size_t v = 1; v < size; ++v) {
    if (parent[v] != -1) {
      long long w = matrix[v][parent[v]];
      mst[v][parent[v]] = w;
      mst[parent[v]][v] = w;
    }
  }

  return mst;
}