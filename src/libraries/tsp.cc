#include "tsp.h"

#include <limits>
#include <random>

namespace tsp {

TsmResult AntColonyOptimizer::Solve() {
  const size_t size = graph_.Size();
  if (size == 0) {
    return {};
  }

  TsmResult result;
  result.distance = std::numeric_limits<double>::infinity();
  InitializePheromones(size);

  for (int iteration = 0; iteration < params_.iterations; ++iteration) {
    std::vector<Ant> ants = CreateAnts(size);

    for (auto& ant : ants) {
      BuildAntPath(ant);
      UpdateBestPath(ant, &result);
    }

    EvaporateAndDepositPheromones(ants);
  }

  if (result.vertices.empty()) {
    return {};
  }

  return result;
}

Ant AntColonyOptimizer::CreateAnt(int start_vertex) const {
  const size_t size = graph_.Size();

  Ant ant;
  ant.start = start_vertex;
  ant.current = start_vertex;
  ant.visited.assign(size, false);
  ant.visited[start_vertex] = true;
  ant.path.push_back(start_vertex);

  return ant;
}

std::vector<Ant> AntColonyOptimizer::CreateAnts(size_t size) {
  std::vector<Ant> ants;
  ants.reserve(params_.ants);
  for (int i = 0; i < params_.ants; ++i) {
    int start = i % static_cast<int>(size);
    ants.push_back(CreateAnt(start));
  }
  return ants;
}

void AntColonyOptimizer::InitializePheromones(size_t size) {
  pheromones_.assign(size, std::vector<double>(size, 1.0));
}

void AntColonyOptimizer::BuildAntPath(Ant& ant) {
  const size_t size = graph_.Size();

  const auto& matrix = graph_.GetAdjecencyMatrix();

  while (ant.path.size() < size) {
    int next = ChooseNextVertex(ant);
    if (next == -1) {
      // путь невозможен, прерываем
      return;
    }
    ant.path.push_back(next);
    ant.distance += matrix[ant.current][next];
    ant.visited[next] = true;
    ant.current = next;
  }

  // возвращаемся в стартовую вершину, если путь возможен
  if (matrix[ant.current][ant.start] != 0) {
    ant.path.push_back(ant.start);
    ant.distance += matrix[ant.current][ant.start];
  }
}

int AntColonyOptimizer::ChooseNextVertex(const Ant& ant) {
  std::vector<int> candidates;
  std::vector<double> probabilities;
  const auto& matrix = graph_.GetAdjecencyMatrix();

  for (size_t i = 0; i < graph_.Size(); ++i) {
    if (!ant.visited[i] && matrix[ant.current][i] > 0) {
      candidates.push_back(static_cast<int>(i));
      double pheromone = pheromones_[ant.current][i];
      double desirability = 1.0 / matrix[ant.current][i];
      probabilities.push_back(std::pow(pheromone, params_.alpha) *
                              std::pow(desirability, params_.beta));
    }
  }

  if (candidates.empty()) return -1;

  // нормируем вероятности
  double sum = std::accumulate(probabilities.begin(), probabilities.end(), 0.0);
  for (auto& p : probabilities) p /= sum;

  // делаем случайный выбор
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  static std::default_random_engine re(
      std::chrono::system_clock::now().time_since_epoch().count());
  double r = dist(re);

  double cumulative = 0.0;
  for (size_t i = 0; i < candidates.size(); ++i) {
    cumulative += probabilities[i];
    if (r <= cumulative) return candidates[i];
  }
  return candidates.back();
}

void AntColonyOptimizer::UpdateBestPath(const Ant& ant, TsmResult* best) {
  if (ant.path.size() == graph_.Size() + 1 && ant.distance < best->distance) {
    best->distance = ant.distance;
    best->vertices = ant.path;
  }
}

void AntColonyOptimizer::EvaporateAndDepositPheromones(
    const std::vector<Ant>& ants) {
  const size_t size = graph_.Size();
  // испарение
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      pheromones_[i][j] *= (1.0 - params_.evaporation);
      if (pheromones_[i][j] < 0.01 && i != j) pheromones_[i][j] = 0.01;
    }
  }

  // добавление феромонов
  for (const auto& ant : ants) {
    if (ant.path.size() != size + 1) continue;  // недопустимый путь
    for (size_t i = 0; i < ant.path.size() - 1; ++i) {
      int from = ant.path[i];
      int to = ant.path[i + 1];
      pheromones_[from][to] += params_.Q / ant.distance;
      pheromones_[to][from] = pheromones_[from][to];
    }
  }
}

}  // namespace tsp
