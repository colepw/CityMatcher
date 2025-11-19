#ifndef UTILITY_H
#define UTILITY_H

#include "User.h"
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

using Graph = std::unordered_map<int, User*>;

static bool BFS(const Graph& g);

static bool DFS(const Graph& g);

int bipartiteMatching(const Graph& g);

#endif // UTILITY_H