#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(LadderTests, BasicLadder) {
  std::set<std::string> word_list = {"plant", "plane", "place", "peace"};
  std::vector<std::string> expected = {"plant", "plane", "place", "peace"};
  EXPECT_EQ(generate_word_ladder("plant", "peace", word_list), expected);
}

TEST(LadderTests, NoLadderExists) {
  std::set<std::string> word_list = {"venus", "jupiter", "saturn"};
  EXPECT_TRUE(generate_word_ladder("mercury", "neptune", word_list).empty());
}

TEST(LadderTests, IdenticalStartEnd) {
  std::set<std::string> word_list = {"pluto"};
  EXPECT_TRUE(generate_word_ladder("pluto", "pluto", word_list).empty());
}

TEST(DijkstraTests, BasicShortestPath) {
  Graph G;
  G.numVertices = 6;
  G.resize(6);
  G[0].push_back({0, 1, 3});
  G[0].push_back({0, 2, 2});
  G[1].push_back({1, 3, 4});
  G[2].push_back({2, 3, 1});
  G[3].push_back({3, 4, 5});
  G[4].push_back({4, 5, 2});

  std::vector<int> previous;
  std::vector<int> distances = dijkstra_shortest_path(G, 0, previous);
  EXPECT_EQ(distances[5], 10);
}

TEST(DijkstraTests, NoPathExists) {
  Graph G;
  G.numVertices = 5;
  G.resize(5);
  G[0].push_back({0, 1, 2});
  G[2].push_back({2, 3, 3});

  std::vector<int> previous;
  std::vector<int> distances = dijkstra_shortest_path(G, 0, previous);
  EXPECT_EQ(distances[3], INF);
}

TEST(DijkstraTests, PathExtraction) {
  std::vector<int> distances = {0, 1, 2, 3};
  std::vector<int> previous = {-1, 0, 2, 1};
  std::vector<int> expected = {0, 1, 3};
  EXPECT_EQ(extract_shortest_path(distances, previous, 3), expected);
}
