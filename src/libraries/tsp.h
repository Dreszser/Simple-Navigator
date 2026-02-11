#ifndef S21_TSP_H_
#define S21_TSP_H_

#include <vector>

#include "graph.h"

namespace tsp {

struct TsmResult {
  std::vector<int> vertices;
  double distance = 0.0;
};

struct Ant {
  int start = -1;
  int current = -1;
  std::vector<bool> visited;
  std::vector<int> path;
  double distance = 0.0;
};

struct ColonyParams {
  int ants = 10;
  int iterations = 100;
  double alpha = 1.0;
  double beta = 2.0;
  double evaporation = 0.5;
  double Q = 100.0;
};

class AntColonyOptimizer {
 public:
  explicit AntColonyOptimizer(const s21::Graph& graph) : graph_(graph) {};
  TsmResult Solve();

 private:
  const s21::Graph& graph_;
  std::vector<std::vector<double>> pheromones_;
  ColonyParams params_;

  Ant CreateAnt(int start_vertex) const;
  std::vector<Ant> CreateAnts(size_t size);
  void InitializePheromones(size_t size);
  void BuildAntPath(Ant& ant);
  int ChooseNextVertex(const Ant& ant);
  void UpdateBestPath(const Ant& ant, TsmResult* best);
  void EvaporateAndDepositPheromones(const std::vector<Ant>& ants);
};

}  // namespace tsp

#endif  // S21_TSP_H_