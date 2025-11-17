#ifndef UTILITY_H
#define UTILITY_H

#include "User.h"
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>

using Graph = std::vector<User*>;

bool BFS(const Graph& g);

bool DFS(const Graph& g);

int bipartiteMatching(const Graph& g);

#endif // UTILITY_H