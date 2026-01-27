#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

#include "graph.h"

std::string ReadFile(const std::string& path) {
  std::ifstream file(path);
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

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

TEST(GraphLoader, MatrixIsLoadedCorrectly) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/valid_graph_1.txt"));

  const auto& m = graph.GetAdjecencyMatrix();
  ASSERT_EQ(graph.Size(), 3u);
  EXPECT_EQ(m[0][1], 1);
  EXPECT_EQ(m[1][2], 3);
}

TEST(GraphExport, SimpleGraphExport) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/valid_graph_1.txt"));

  const std::string output = "libraries/tests/output/simple.dot";
  ASSERT_TRUE(graph.ExportGraphToDot(output));

  const std::string dot = ReadFile(output);

  const std::string expected =
      "graph G {\n"
      "\t1 -- 2 [label=1]\n"
      "\t1 -- 3 [label=2]\n"
      "\t2 -- 3 [label=3]\n"
      "}\n";

  EXPECT_EQ(dot, expected);
}

TEST(GraphExport, InvalidPathFails) {
  Graph graph;
  ASSERT_TRUE(
      graph.LoadGraphFromFile("libraries/tests/data/valid_graph_1.txt"));

  EXPECT_FALSE(graph.ExportGraphToDot("/invalid/path/out.dot"));
}
