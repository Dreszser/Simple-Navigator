#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

#include "graph.h"
#include "graph_algorithms.h"

using namespace s21;

TEST(BFSTests, BFSFailTest1) {
  Graph graph;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, 4), std::vector<int>());
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, 0), std::vector<int>());
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, 6), std::vector<int>());
}

TEST(BFSTests, BFSSimpleTest1) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {1, 2, 3, 4, 5};
  const int start_vertex = 1;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, start_vertex), check);
}

TEST(BFSTests, BFSSimpleTest2) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {2, 1, 3, 5, 4};
  const int start_vertex = 2;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, start_vertex), check);
}

TEST(BFSTests, BFSSimpleTest3) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {3, 1, 2, 4, 5};
  const int start_vertex = 3;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, start_vertex), check);
}

TEST(BFSTests, BFSSimpleTest4) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {4, 1, 3, 5, 2};
  const int start_vertex = 4;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, start_vertex), check);
}

TEST(BFSTests, BFSSimpleTest5) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {5, 1, 2, 3, 4};
  const int start_vertex = 5;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, start_vertex), check);
}

TEST(DFSTests, DFSFailTest1) {
  Graph graph;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, 4), std::vector<int>());
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, 0), std::vector<int>());
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, 6), std::vector<int>());
}

TEST(DFSTests, DFSSimpleTest1) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {1, 2, 3, 4, 5};
  const int start_vertex = 1;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, start_vertex), check);
}

TEST(DFSTests, DFSSimpleTest2) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {2, 1, 3, 4, 5};
  const int start_vertex = 2;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, start_vertex), check);
}

TEST(DFSTests, DFSSimpleTest3) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {3, 1, 2, 5, 4};
  const int start_vertex = 3;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, start_vertex), check);
}

TEST(DFSTests, DFSSimpleTest4) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {4, 1, 2, 3, 5};
  const int start_vertex = 4;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, start_vertex), check);
}

TEST(DFSTests, DFSSimpleTest5) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {5, 1, 2, 3, 4};
  const int start_vertex = 5;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, start_vertex), check);
}

TEST(DijkstraTests, DijkstraFailTest1) {
  Graph graph;
  const int fail_code = -1;
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 1),
            fail_code);
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 0, 1),
            fail_code);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 0),
            fail_code);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 6, 1),
            fail_code);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 6),
            fail_code);
}

TEST(DijkstraTests, DijkstraFailTest2) {
  Graph graph;
  const int fail_code = -1;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/overflow_graph.txt"));
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 3),
            fail_code);
}

TEST(DijkstraTests, DijkstrasTest1) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  const int check = 2;
  const int start_vertex = 5;
  const int finish_vertex = 1;
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, start_vertex,
                                                            finish_vertex),
            check);
}

TEST(DijkstraTests, DijkstrasTest2) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  const int check = 3;
  const int start_vertex = 2;
  const int finish_vertex = 3;
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, start_vertex,
                                                            finish_vertex),
            check);
}

TEST(DijkstraTests, DijkstrasTest3) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  const int check = 2;
  const int start_vertex = 2;
  const int finish_vertex = 4;
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, start_vertex,
                                                            finish_vertex),
            check);
}

TEST(FloydWarshallTests, FloydWarshallTest1) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  const std::vector<std::vector<long long>> check = {{0, 1, 2, 3, 2},
                                                     {1, 0, 3, 2, 1},
                                                     {2, 3, 0, 3, 4},
                                                     {3, 2, 3, 0, 1},
                                                     {2, 1, 4, 1, 0}};
  EXPECT_EQ(GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph), check);
}

TEST(FloydWarshallTests, FloydWarshallOverflow) {
  Graph graph;
  ASSERT_TRUE(graph.LoadGraphFromFile("tests/data/fw_overflow.txt"));
  const std::vector<std::vector<long long>> check = {
      {0, 0, 0}, {0, 0, 1}, {0, 1, 0}};
  EXPECT_EQ(GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph), check);
}

TEST(FloydWarshallTests, FloydWarshallFail) {
  Graph graph;
  EXPECT_EQ(GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph),
            std::vector<std::vector<long long>>());
}

TEST(PrimmTests, PrimmDisconnectedGraph) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/valid_graph_2.txt"));

  auto mst = GraphAlgorithms::GetLeastSpanningTree(graph);
  std::vector<std::vector<long long>> expected;
  EXPECT_EQ(mst, expected);
}

TEST(PrimmTests, PrimmTest) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  const std::vector<std::vector<long long>> check = {{0, 1, 2, 0, 0},
                                                     {1, 0, 0, 0, 1},
                                                     {2, 0, 0, 0, 0},
                                                     {0, 0, 0, 0, 1},
                                                     {0, 1, 0, 1, 0}};
  EXPECT_EQ(GraphAlgorithms::GetLeastSpanningTree(graph), check);
}

TEST(PrimmTests, PrimmEmptyGraph) {
  Graph graph;
  auto mst = GraphAlgorithms::GetLeastSpanningTree(graph);
  std::vector<std::vector<long long>> expected;
  EXPECT_EQ(mst, expected);
}

TEST(IsTourValidTests, IsTourValidTest1) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  tsp::TsmResult valid{.vertices = {1, 2, 5, 4, 3, 1}, .distance = 8.0};
  EXPECT_TRUE(tsp::TspValidator::IsTourValid(graph, valid));
}

TEST(IsTourValidTests, IsTourValidTest2) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  tsp::TsmResult no_return{.vertices = {1, 2, 5, 4, 3}, .distance = 7.0};
  EXPECT_FALSE(tsp::TspValidator::IsTourValid(graph, no_return));
}

TEST(IsTourValidTests, IsTourValidTest3) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  tsp::TsmResult wrong_cycle{.vertices = {1, 2, 5, 4, 3, 2}, .distance = 8.0};
  EXPECT_FALSE(tsp::TspValidator::IsTourValid(graph, wrong_cycle));
}

TEST(IsTourValidTests, IsTourValidTest4) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  tsp::TsmResult duplicate_vertex{.vertices = {1, 2, 5, 2, 3, 1},
                                  .distance = 8.0};
  EXPECT_FALSE(tsp::TspValidator::IsTourValid(graph, duplicate_vertex));
}

TEST(IsTourValidTests, IsTourValidTest5) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  tsp::TsmResult no_edge{.vertices = {1, 2, 4, 5, 3, 1}, .distance = 10.0};
  EXPECT_FALSE(tsp::TspValidator::IsTourValid(graph, no_edge));
}

TEST(IsTourValidTests, IsTourValtidTest6) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  tsp::TsmResult wrong_distance{.vertices = {1, 2, 5, 4, 3, 1},
                                .distance = 10.0};
  EXPECT_FALSE(tsp::TspValidator::IsTourValid(graph, wrong_distance));
}

TEST(IsTourValidTests, IsTourValidTest7) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));
  tsp::TsmResult zero_distance{.vertices = {1, 2, 5, 4, 3, 1}, .distance = 0.0};
  EXPECT_FALSE(tsp::TspValidator::IsTourValid(graph, zero_distance));
}

TEST(TSPTests, AntColonyTest1) {
  Graph graph;
  ASSERT_TRUE(graph.LoadGraphFromFile(
      "tests/data/travelling_salesman_problem_graph.txt"));

  const double optimal = 253.0;

  for (int i = 0; i < 5; ++i) {
    tsp::TsmResult res = GraphAlgorithms::SolveTravelingSalesmanProblem(graph);

    EXPECT_TRUE(tsp::TspValidator::IsTourValid(graph, res));
    EXPECT_GE(res.distance, optimal);
    EXPECT_LE(res.distance, optimal + 2.0);
  }
}

TEST(TSPTests, AntColonyTest2) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("tests/data/algorithm_graph.txt"));

  const double optimal = 8.0;

  for (int i = 0; i < 5; ++i) {
    tsp::TsmResult res = GraphAlgorithms::SolveTravelingSalesmanProblem(graph);

    EXPECT_TRUE(tsp::TspValidator::IsTourValid(graph, res));
    EXPECT_GE(res.distance, optimal);
    EXPECT_LE(res.distance, optimal + 2.0);
  }
}

TEST(TSPTests, AntColonyTest3) {
  Graph graph;
  ASSERT_TRUE(graph.LoadGraphFromFile("tests/data/tsp_test.txt"));

  const double optimal = 69.0;

  for (int i = 0; i < 5; ++i) {
    tsp::TsmResult res = GraphAlgorithms::SolveTravelingSalesmanProblem(graph);

    EXPECT_TRUE(tsp::TspValidator::IsTourValid(graph, res));
    EXPECT_GE(res.distance, optimal);
    EXPECT_LE(res.distance, optimal + 2.0);
  }
}

TEST(TSPTests, AntColonyFail1) {
  Graph graph;
  tsp::TsmResult res = GraphAlgorithms::SolveTravelingSalesmanProblem(graph);
  EXPECT_FALSE(tsp::TspValidator::IsTourValid(graph, res));
}