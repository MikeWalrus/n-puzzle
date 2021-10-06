// Copyright 2021 Liao Junxuan

// This file is part of n-puzzle.

// n-puzzle is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// n-puzzle is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with n-puzzle.  If not, see <https://www.gnu.org/licenses/>.

#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include "problem.h"
void solve_bfs(struct Problem *problem);
void solve_dfs(struct Problem *problem);
void solve_branch_and_bound(struct Problem *problem);
void solve_hill_climbing(struct Problem *problem);
void solve_best_first(struct Problem *problem);
void solve_a_star(struct Problem *problem);

struct Algorithm {
    const char * name;
    Solution solution;
};

static struct Algorithm algorithms[] = 
{
    {"bfs", solve_bfs},
    {"dfs", solve_dfs},
    {"bnb", solve_branch_and_bound},
    {"hill_climbing", solve_hill_climbing},
    {"best_first", solve_best_first},
    {"a_star", solve_a_star}
};

#endif
