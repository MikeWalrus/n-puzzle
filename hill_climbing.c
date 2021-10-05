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

#include <stddef.h>

#include "problem.h"

static void children_delete_others(struct TreeNode **children, struct TreeNode *the_one, int size)
{
    for (struct TreeNode **p = children; *p; p++) {
        struct TreeNode *child = *p;
        if (child != the_one)
            tree_node_delete(child, size);
    }
    *children = the_one;
    children[1] = NULL;
}

void solve_hill_climbing(struct Problem *problem)
{
    int size = problem->size;
    struct State *goal = &problem->goal;
    struct TreeNode *root = tree_node_new(&problem->init_state, 0, 0);

    problem->result.tree = root;
    int min_heuristic = root->heuristic = get_h(root->state, &problem->goal, size);
    struct TreeNode *node = root;
    for (; ; ) {
        struct TreeNode **children = tree_node_expand(node, size);
        struct TreeNode *next_step = NULL;
        for (struct TreeNode **p = children; *p; p++) {
            struct TreeNode *child = *p;
            if (state_is_equal(child->state, goal, size)) {
                fill_result(child, &problem->result);
                return;
            }

            int heuristic = child->heuristic = get_h(child->state, goal, size);
            if (heuristic < min_heuristic) {
                min_heuristic = heuristic;
                next_step = child;
            }
        }
        if (!next_step)
            return; // Can't solve.
        children_delete_others(children, next_step, size);
        node = next_step;
    }
}
