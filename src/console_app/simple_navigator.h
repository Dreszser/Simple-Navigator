#ifndef S21_SIMPLE_NAVIGATOR_H_
#define S21_SIMPLE_NAVIGATOR_H_

#include "graph.h"
#include "graph_algorithms.h"

namespace s21 {

class SimpleNavigatorApp {
 public:
  void Run();

 private:
  void PrintMenu() const;
  void HandleCommand(int command);

  void WaitForEnter() const;
  void PrintHeader() const;
  void ClearScreen() const;

  void LoadGraph();
  void ExportGraph();
  void TraverseBfs();
  void TraverseDfs();
  void ShortestPath();
  void AllPairsShortestPath();
  void MinimumSpanningTree();
  void SolveTsp();

  void PrintMessage(const std::string& error) const;
  void PrintVector(const std::vector<int>& v, const std::string& label = "");
  template <typename T>
  void PrintAdjacencyMatrix(const std::vector<std::vector<T>>& matrix,
                            const std::string& label = "");
  bool ReadInt(int& value);

  Graph graph_;
  bool graph_loaded_ = false;
};

}  // namespace s21

#endif  // S21_SIMPLE_NAVIGATOR_H_
