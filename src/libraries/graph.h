#ifndef S21_GRAPH_H_
#define S21_GRAPH_H_

#include <string>
#include <vector>

class Graph {
 public:
  Graph() = default;

  bool LoadGraphFromFile(const std::string& filename);
  bool ExportGraphToDot(const std::string& filename);

  size_t Size() const;
  const std::vector<std::vector<int>>& GetAdjecencyMatrix() const;

 private:
  std::vector<std::vector<int>> adjacency_matrix_;

  bool ValidateGraph(const std::vector<std::vector<int>>& adj_matrix);
};

#endif  // S21_GRAPH_H_