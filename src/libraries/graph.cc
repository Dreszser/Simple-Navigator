#include <graph.h>

#include <fstream>

bool Graph::LoadGraphFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    return false;
  }

  size_t size = 0;
  file >> size;
  if (file.fail() || size <= 0) {
    return false;
  }

  std::vector<std::vector<int>> temp(size, std::vector<int>(size, 0));
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      int weight = 0;
      file >> weight;
      if (file.fail() || weight < 0) {
        return false;
      }
      temp[i][j] = weight;
    }
  }

  if (!ValidateGraph(temp)) return false;

  adjacency_matrix_ = std::move(temp);
  return true;
}

bool Graph::ValidateGraph(const std::vector<std::vector<int>>& adj_matrix) {
  size_t size = adj_matrix.size();

  for (size_t i = 0; i < size; ++i) {
    for (size_t j = i + 1; j < size; ++j) {
      if (adj_matrix[i][j] != adj_matrix[j][i]) {
        return false;
      }
    }
  }

  bool has_edge = false;
  for (size_t i = 0; i < size && !has_edge; ++i) {
    for (size_t j = 0; j < size; ++j) {
      if (adj_matrix[i][j] != 0) {
        has_edge = true;
        break;
      }
    }
  }
  if (!has_edge) {
    return false;
  }

  return true;
}