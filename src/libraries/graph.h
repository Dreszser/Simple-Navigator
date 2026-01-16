#ifndef S21_GRAPH_H_
#define S21_GRAPH_H_

#include <string>
#include <vector>

class Graph {
 public:
  Graph() = default;

  void LoadGraphFromFile(const std::string& filename);
  void ExportGraphToDot(const std::string& filename);

  size_t Size() const;
  const std::vector<std::vector<int>>& GetAdjecencyMatrix() const;

 private:
  std::vector<std::vector<int>> adjacency_matrix_;
};

#endif  // S21_GRAPH_H_