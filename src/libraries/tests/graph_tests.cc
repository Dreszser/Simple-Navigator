#include <gtest/gtest.h>

#include "graph.h"

TEST(GraphLoader, ValidGraphLoadsSuccessfully1) {
  Graph graph;
  EXPECT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/valid_graph_1.txt"));
}

TEST(GraphLoader, ValidGraphLoadsSuccessfully2) {
  Graph graph;
  EXPECT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/valid_graph_2.txt"));
}

TEST(GraphLoader, NonSymmetricGraphFails) {
  Graph graph;
  EXPECT_FALSE(graph.LoadGraphFromFile(
      "libraries/tests/data/invalid_non_symmetric.txt"));
}

TEST(GraphLoader, NegativeWeightFails) {
  Graph graph;
  EXPECT_FALSE(graph.LoadGraphFromFile(
      "libraries/tests/data/invalid_negative_weight.txt"));
}

TEST(GraphLoader, EmptyGraphFails) {
  Graph graph;
  EXPECT_FALSE(
      graph.LoadGraphFromFile("libraries/tests/data/invalid_empty_graph.txt"));
}

TEST(GraphLoader, TruncatedFileFails) {
  Graph graph;
  EXPECT_FALSE(
      graph.LoadGraphFromFile("libraries/tests/data/invalid_truncated.txt"));
}

// TEST(GraphLoader, MatrixIsLoadedCorrectly) {
//   Graph graph;
//   ASSERT_TRUE(graph.LoadGraphFromFile("tests/data/valid_graph_1.txt"));

//   const auto& m = graph.GetAdjacencyMatrix();
//   ASSERT_EQ(m.size(), 3u);
//   EXPECT_EQ(m[0][1], 1);
//   EXPECT_EQ(m[1][2], 3);
// }
