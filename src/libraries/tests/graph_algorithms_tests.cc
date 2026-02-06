#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

#include "graph.h"
#include "graph_algorithms.h"

TEST(AlgorithmsTests, BFSFailTest1) {
  Graph graph;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, 4), std::vector<int>());
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, 0), std::vector<int>());
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, 6), std::vector<int>());
}

TEST(AlgorithmsTests, BFSSimpleTest1) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {1, 2, 3, 4, 5};
  const int start_vertex = 1;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, BFSSimpleTest2) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {2, 1, 3, 5, 4};
  const int start_vertex = 2;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, BFSSimpleTest3) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {3, 1, 2, 4, 5};
  const int start_vertex = 3;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, BFSSimpleTest4) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {4, 1, 3, 5, 2};
  const int start_vertex = 4;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, BFSSimpleTest5) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {5, 1, 2, 3, 4};
  const int start_vertex = 5;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, DFSFailTest1) {
  Graph graph;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, 4), std::vector<int>());
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, 0), std::vector<int>());
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, 6), std::vector<int>());
}

TEST(AlgorithmsTests, DFSSimpleTest1) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {1, 2, 3, 4, 5};
  const int start_vertex = 1;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, DFSSimpleTest2) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {2, 1, 3, 4, 5};
  const int start_vertex = 2;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, DFSSimpleTest3) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {3, 1, 2, 5, 4};
  const int start_vertex = 3;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, DFSSimpleTest4) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {4, 1, 2, 3, 5};
  const int start_vertex = 4;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, DFSSimpleTest5) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {5, 1, 2, 3, 4};
  const int start_vertex = 5;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, DijkstraFailTest1) {
  Graph graph;
  const int fail_code = -1;
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 1),
            fail_code);
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 0, 1),
            fail_code);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 0),
            fail_code);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 6, 1),
            fail_code);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 6),
            fail_code);
}

TEST(AlgorithmsTests, DijkstraFailTest2) {
  Graph graph;
  const int fail_code = -1;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/overflow_graph.txt"));
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 3),
            fail_code);
}

TEST(AlgorithmsTests, DijkstrasTest1) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const int check = 2;
  const int start_vertex = 5;
  const int finish_vertex = 1;
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, start_vertex,
                                                            finish_vertex),
            check);
}

TEST(AlgorithmsTests, DijkstrasTest2) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const int check = 3;
  const int start_vertex = 2;
  const int finish_vertex = 3;
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, start_vertex,
                                                            finish_vertex),
            check);
}

TEST(AlgorithmsTests, DijkstrasTest3) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const int check = 2;
  const int start_vertex = 2;
  const int finish_vertex = 4;
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, start_vertex,
                                                            finish_vertex),
            check);
}

TEST(AlgorithmsTests, FloydWarshallTest1) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<std::vector<long long>> check = {{0, 1, 2, 3, 2},
                                                     {1, 0, 3, 2, 1},
                                                     {2, 3, 0, 3, 4},
                                                     {3, 2, 3, 0, 1},
                                                     {2, 1, 4, 1, 0}};
  EXPECT_EQ(GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph), check);
}

TEST(AlgorithmsTests, FloydWarshallOverflow) {
  Graph graph;
  ASSERT_TRUE(graph.LoadGraphFromFile("libraries/tests/data/fw_overflow.txt"));
  const std::vector<std::vector<long long>> check = {
      {0, 0, 0}, {0, 0, 1}, {0, 1, 0}};
  EXPECT_EQ(GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph), check);
}

TEST(AlgorithmsTests, FloydWarshallFail) {
  Graph graph;
  EXPECT_EQ(GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph),
            std::vector<std::vector<long long>>());
}

TEST(AlgorithmsTests, PrimmDisconnectedGraph) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/valid_graph_2.txt"));

  auto mst = GraphAlgorithms::GetLeastSpanningTree(graph);
  std::vector<std::vector<long long>> expected;
  EXPECT_EQ(mst, expected);
}

TEST(AlgoritmsTests, PrimmTest) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<std::vector<long long>> check = {{0, 1, 2, 0, 0},
                                                     {1, 0, 0, 0, 1},
                                                     {2, 0, 0, 0, 0},
                                                     {0, 0, 0, 0, 1},
                                                     {0, 1, 0, 1, 0}};
  EXPECT_EQ(GraphAlgorithms::GetLeastSpanningTree(graph), check);
}

TEST(AlgorithmsTests, PrimmEmptyGraph) {
  Graph graph;
  auto mst = GraphAlgorithms::GetLeastSpanningTree(graph);
  std::vector<std::vector<long long>> expected;
  EXPECT_EQ(mst, expected);
}