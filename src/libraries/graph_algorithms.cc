#include "graph_algorithms.h"

namespace s21 {

std::vector<int> GraphAlgorithms::DepthFirstSearch(const Graph& graph,
                                                   int start_vertex) {
  std::vector<int> route;
  const size_t size = graph.Size();
  if (size == 0 || start_vertex < 1 ||
      static_cast<size_t>(start_vertex) > size) {
    return route;
  }

  const auto& matrix = graph.GetAdjacencyMatrix();

  std::vector<bool> visited(size, false);
  s21::Stack<int> stack;

  const int start_vertex_index = start_vertex - 1;
  stack.push(start_vertex_index);

  /* DFS algorithm */
  while (!stack.empty()) {
    int current = stack.top();
    stack.pop();

    if (visited[current]) continue;
    visited[current] = true;

    route.push_back(current + 1);
    for (int neighbor = static_cast<int>(size) - 1; neighbor >= 0; --neighbor) {
      if (matrix[current][neighbor] != 0 && !visited[neighbor]) {
        stack.push(neighbor);
      }
    }
  }

  return route;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph& graph,
                                                     int start_vertex) {
  std::vector<int> route;
  const size_t size = graph.Size();
  if (size == 0 || start_vertex < 1 ||
      static_cast<size_t>(start_vertex) > size) {
    return route;
  }

  const auto& matrix = graph.GetAdjacencyMatrix();

  std::vector<bool> visited(size, false);
  s21::Queue<int> queue;

  const int start_vertex_index = start_vertex - 1;
  visited[start_vertex_index] = true;
  queue.push(start_vertex_index);

  /* BFS algorithm */
  while (!queue.empty()) {
    int current = queue.front();
    queue.pop();

    int vertex_label = current + 1;
    route.push_back(vertex_label);

    for (size_t neighbor = 0; neighbor < size; ++neighbor) {
      if (matrix[current][neighbor] != 0 && !visited[neighbor]) {
        visited[neighbor] = true;
        queue.push(static_cast<int>(neighbor));
      }
    }
  }

  return route;
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

  const auto& matrix = graph.GetAdjacencyMatrix();

  const size_t start_vertex_index = vertex1 - 1;
  const size_t finish_vertex_index = vertex2 - 1;

  /* trying to prevent possible overflow */
  std::vector<Distance> distance(size, INF);
  std::vector<bool> visited(size, false);

  distance[start_vertex_index] = 0;

  /* Dijkstra's algorithm */
  for (size_t i = 0; i < size; ++i) {
    int current = FindNearestUnvisitedVertex(distance, visited);
    if (current == -1 || distance[current] == INF) break;

    visited[current] = true;

    for (size_t neighbor = 0; neighbor < size; ++neighbor) {
      if (!visited[neighbor] && matrix[current][neighbor] > 0) {
        const Distance candidate =
            distance[current] + matrix[current][neighbor];
        distance[neighbor] = std::min(candidate, distance[neighbor]);
      }
    }
  }

  if (distance[finish_vertex_index] > std::numeric_limits<int>::max())
    return -1;
  return (distance[finish_vertex_index] == INF) ? -1
                                                : distance[finish_vertex_index];
}

int GraphAlgorithms::FindNearestUnvisitedVertex(
    const std::vector<long long>& distance, const std::vector<bool>& visited) {
  int nearest_vertex_index = -1;
  for (size_t vertex_index = 0; vertex_index < distance.size();
       ++vertex_index) {
    if (!visited[vertex_index] &&
        (nearest_vertex_index == -1 ||
         distance[vertex_index] < distance[nearest_vertex_index]))
      nearest_vertex_index = static_cast<int>(vertex_index);
  }
  return nearest_vertex_index;
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
  const auto& matrix = graph.GetAdjacencyMatrix();

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

  const auto& matrix = graph.GetAdjacencyMatrix();

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

tsp::TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(
    const Graph& graph) {
  tsp::AntColonyOptimizer aco(graph);
  return aco.Solve();
}

}  // namespace s21
