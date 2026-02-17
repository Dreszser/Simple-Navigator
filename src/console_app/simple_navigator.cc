#include "simple_navigator.h"

#include <iomanip>
#include <iostream>

namespace s21 {

void SimpleNavigatorApp::Run() {
  while (true) {
    ClearScreen();
    PrintHeader();
    PrintMenu();

    int command;
    if (!ReadInt(command)) {
      PrintMessage("Unknown command");
    } else if (command == 0) {
      break;
    } else {
      HandleCommand(command);
    }
  }
}

void SimpleNavigatorApp::PrintMenu() const {
  std::cout << "\n=== Simple Navigator ===\n";
  std::cout << "1. Load graph from file\n";
  std::cout << "2. Export graph to DOT\n";
  std::cout << "3. Breadth-first traversal\n";
  std::cout << "4. Depth-first traversal\n";
  std::cout << "5. Shortest path between vertices\n";
  std::cout << "6. All-pairs shortest paths\n";
  std::cout << "7. Minimum spanning tree\n";
  std::cout << "8. Solve Traveling Salesman Problem\n";
  std::cout << "0. Exit\n\n";
  std::cout << "Choose option: ";
}

void SimpleNavigatorApp::HandleCommand(int command) {
  switch (command) {
    case 1:
      LoadGraph();
      break;
    case 2:
      ExportGraph();
      break;
    case 3:
      BreadthFirstSearch();
      break;
    case 4:
      DepthFirstSearch();
      break;
    case 5:
      ShortestPath();
      break;
    case 6:
      AllPairsShortestPath();
      break;
    case 7:
      MinimumSpanningTree();
      break;
    case 8:
      SolveTsp();
      break;
    default:
      PrintMessage("Unknown command");
      break;
  }
}

void SimpleNavigatorApp::LoadGraph() {
  std::string filename;
  std::cout << "Enter filename: ";
  std::getline(std::cin, filename);

  if (graph_.LoadGraphFromFile(filename)) {
    graph_loaded_ = true;
    PrintMessage("Graph loaded successfully");
  } else {
    PrintMessage("Failed to load graph");
  }
}

void SimpleNavigatorApp::ExportGraph() {
  if (graph_loaded_) {
    std::string filename;
    std::cout << "Enter filename: ";
    std::getline(std::cin, filename);

    if (graph_.ExportGraphToDot(filename)) {
      PrintMessage("Graph exported successfully");
    } else {
      PrintMessage("Failed to export graph");
    }
  } else {
    PrintMessage("Graph is not loaded");
  }
}

void SimpleNavigatorApp::BreadthFirstSearch() {
  if (graph_loaded_) {
    std::vector<int> result;
    int start_vertex;
    std::cout << "Enter start vertex: ";
    if (!ReadInt(start_vertex)) {
      PrintMessage("Invalid input");
      return;
    }

    result = s21::GraphAlgorithms::BreadthFirstSearch(graph_, start_vertex);

    if (!result.empty()) {
      ClearScreen();
      PrintVector(result, "BFS");
      WaitForEnter();
    } else {
      PrintMessage("Failed to perform Breadth First Search");
    }
  } else {
    PrintMessage("Graph is not loaded");
  }
}

void SimpleNavigatorApp::DepthFirstSearch() {
  if (graph_loaded_) {
    std::vector<int> result;
    int start_vertex;
    std::cout << "Enter start vertex: ";
    if (!ReadInt(start_vertex)) {
      PrintMessage("Invalid input");
      return;
    }

    result = s21::GraphAlgorithms::DepthFirstSearch(graph_, start_vertex);

    if (!result.empty()) {
      ClearScreen();
      PrintVector(result, "DFS");
      WaitForEnter();
    } else {
      PrintMessage("Failed to perform Depth First Search");
    }
  } else {
    PrintMessage("Graph is not loaded");
  }
}

void SimpleNavigatorApp::ShortestPath() {
  if (graph_loaded_) {
    int start_vertex;
    int finish_vertex;
    std::cout << "Enter first vertex: ";
    if (!ReadInt(start_vertex)) {
      PrintMessage("Invalid input");
      return;
    }
    std::cout << "Enter second vertex: ";
    if (!ReadInt(finish_vertex)) {
      PrintMessage("Invalid input");
      return;
    }

    int result = s21::GraphAlgorithms::GetShortestPathBetweenVertices(
        graph_, start_vertex, finish_vertex);

    if (result != -1) {
      ClearScreen();
      std::cout << "Shortest path length: " << result << "\n";
      WaitForEnter();
    } else {
      PrintMessage("Failed to find the shortest path between vertices");
    }
  } else {
    PrintMessage("Graph is not loaded");
  }
}

void SimpleNavigatorApp::AllPairsShortestPath() {
  if (graph_loaded_) {
    std::vector<std::vector<long long>> result =
        s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph_);

    if (!result.empty()) {
      ClearScreen();
      PrintAdjacencyMatrix(result, "Shortest paths between all vertices");
      WaitForEnter();
    } else {
      PrintMessage("Failed to find shortest paths between all vertices");
    }
  } else {
    PrintMessage("Graph is not loaded");
  }
}

void SimpleNavigatorApp::MinimumSpanningTree() {
  if (graph_loaded_) {
    std::vector<std::vector<long long>> result =
        s21::GraphAlgorithms::GetLeastSpanningTree(graph_);

    if (!result.empty()) {
      ClearScreen();
      PrintAdjacencyMatrix(result, "Minimum Spanning Tree");
      WaitForEnter();
    } else {
      PrintMessage("Failed to find minimum spanning tree");
    }
  } else {
    PrintMessage("Graph is not loaded");
  }
}

void SimpleNavigatorApp::SolveTsp() {
  if (graph_loaded_) {
    tsp::TsmResult result =
        s21::GraphAlgorithms::SolveTravelingSalesmanProblem(graph_);

    if (!result.vertices.empty()) {
      ClearScreen();
      PrintVector(result.vertices, "Traveling Salesman path");
      std::cout << "Distance: " << result.distance << "\n";
      WaitForEnter();
    } else {
      PrintMessage("Failed to solve traveling salesman problem");
    }
  } else {
    PrintMessage("Graph is not loaded");
  }
}

void SimpleNavigatorApp::WaitForEnter() const {
  std::cout << "\nPress Enter to continue...";
  std::string _;
  std::getline(std::cin, _);
}

void SimpleNavigatorApp::PrintHeader() const {
  std::cout << "========================================\n";
  std::cout << "Graph loaded: " << (graph_loaded_ ? "YES" : "NO") << "\n";
  if (graph_loaded_) {
    std::cout << "Vertices: " << graph_.Size() << "\n";
  }
  std::cout << "========================================\n\n";
}

void SimpleNavigatorApp::ClearScreen() const { system("clear"); }

void SimpleNavigatorApp::PrintMessage(const std::string& error) const {
  ClearScreen();
  std::cout << error << "\n";
  WaitForEnter();
  return;
}

void SimpleNavigatorApp::PrintVector(const std::vector<int>& v,
                                     const std::string& label) {
  if (!label.empty()) {
    std::cout << label << ": ";
  }

  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i];
    if (i + 1 < v.size()) std::cout << " -> ";
  }
  std::cout << '\n';
}

template <typename T>
void SimpleNavigatorApp::PrintAdjacencyMatrix(
    const std::vector<std::vector<T>>& matrix, const std::string& label) {
  if (!label.empty()) {
    std::cout << label << ":\n";
  }

  for (const auto& row : matrix) {
    for (const auto& value : row) {
      std::cout << std::setw(6) << value;
    }
    std::cout << '\n';
  }
}

bool SimpleNavigatorApp::ReadInt(int& value) {
  std::string line;
  if (!std::getline(std::cin, line)) {
    return false;
  }

  try {
    size_t pos;
    value = std::stoi(line, &pos);
    return pos == line.size();
  } catch (...) {
    return false;
  }
}

}  // namespace s21