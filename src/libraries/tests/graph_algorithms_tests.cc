#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

#include "graph.h"
#include "graph_algorithms.h"

TEST(AlgorithmsTests, BFSFailTest1) {
  Graph graph;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, 4), std::vector<int>());
  EXPECT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, 0), std::vector<int>());
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, 6), std::vector<int>());
}

TEST(AlgorithmsTests, BFSSimpleTest1) {
  Graph graph;
  EXPECT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {1, 2, 3, 4, 5};
  const int start_vertex = 1;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, BFSSimpleTest2) {
  Graph graph;
  EXPECT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {2, 1, 3, 5, 4};
  const int start_vertex = 2;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, BFSSimpleTest3) {
  Graph graph;
  EXPECT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {3, 1, 2, 4, 5};
  const int start_vertex = 3;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, BFSSimpleTest4) {
  Graph graph;
  EXPECT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {4, 1, 3, 5, 2};
  const int start_vertex = 4;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, BFSSimpleTest5) {
  Graph graph;
  EXPECT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {5, 1, 2, 3, 4};
  const int start_vertex = 5;
  EXPECT_EQ(GraphAlgorithms::BreadthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, DFSFailTest1) {
  Graph graph;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, 4), std::vector<int>());
  EXPECT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, 0), std::vector<int>());
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, 6), std::vector<int>());
}

TEST(AlgorithmsTests, DFSSimpleTest1) {
  Graph graph;
  EXPECT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {1, 2, 3, 4, 5};
  const int start_vertex = 1;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, DFSSimpleTest2) {
  Graph graph;
  EXPECT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {2, 1, 3, 4, 5};
  const int start_vertex = 2;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, DFSSimpleTest3) {
  Graph graph;
  EXPECT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {3, 1, 2, 5, 4};
  const int start_vertex = 3;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, DFSSimpleTest4) {
  Graph graph;
  EXPECT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {4, 1, 2, 3, 5};
  const int start_vertex = 4;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, start_vertex), check);
}

TEST(AlgorithmsTests, DFSSimpleTest5) {
  Graph graph;
  EXPECT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/algorithm_graph.txt"));
  const std::vector<int> check = {5, 1, 2, 3, 4};
  const int start_vertex = 5;
  EXPECT_EQ(GraphAlgorithms::DepthFirstSearch(graph, start_vertex), check);
}