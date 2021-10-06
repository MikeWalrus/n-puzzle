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
// along with n-puzzle.  If not, see <https://www.gnu.org/licenses/>

#include "problem.h"
#include "list.h"
#include "hash_set.h"
#include "utilities.h"

void solve_best_first(struct Problem *problem)
{
    struct List open_list;
    list_init(&open_list);

    struct HashSet *visited = hash_set_new();

    int size = problem->size;
    struct State *goal = &problem->goal;
    struct TreeNode *root = tree_node_new(&problem->init_state, 0, 0);

    list_push(&open_list, root);
    root->heuristic = get_h(root->state, goal, size);
    hash_set_found_or_add(visited, root->state, size);
    do {
        struct TreeNode *node = list_pop_min(&open_list);
        if (state_is_equal(node->state, &problem->goal, size)) {
            fill_result(node, &problem->result);
            break;
        }

        struct TreeNode ** children = tree_node_expand(node, size);
        for (; *children; children++) {
            struct TreeNode *child = *children;
            if (!hash_set_found_or_add(visited, child->state, size)) {
                list_push(&open_list, child);
                child->heuristic = get_h(child->state, goal, size);
            } else
                child->is_deleted = true;
        }
    } while (!list_is_empty(&open_list));
    problem->result.tree = root;
    list_delete(&open_list);
    hash_set_delete(visited);
    return;
}
