#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include "problem.h"
void solve_bfs(struct Problem *problem);
void solve_dfs(struct Problem *problem);
void solve_branch_and_bound(struct Problem *problem);

struct Algorithm {
    const char * name;
    Solution solution;
};

static struct Algorithm algorithms[] = 
{
{"bfs", solve_bfs},
{"dfs", solve_dfs},
{"bnb", solve_branch_and_bound},
};

#endif
