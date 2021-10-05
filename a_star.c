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
#include "list.h"
#include "hash_set.h"

void tree_node_update_depth(struct TreeNode *node, int difference)
{
    node->has_changed = true;
    node->depth += difference;
    node->heuristic += difference;
}

void tree_update_depth(struct TreeNode *node, int difference)
{
    tree_node_update_depth(node, difference);
    for (struct TreeNode **child = node->child; *child; child++) {
        tree_node_update_depth(*child, difference);
    }
}

void delete_child(struct TreeNode **child)
{
    struct TreeNode ** delete_this = child;
    while (*(child + 1))
        child++;
    *delete_this = *child;
    *child = NULL;
}

struct TreeNode ** find_child(struct TreeNode **children, struct TreeNode *child)
{
    for (; *children != child; children++);
    return children;
}

void solve_a_star(struct Problem *problem)
{
    struct List open_list;
    list_init(&open_list);
    struct HashMap *visited = hash_map_new();

    struct State *goal = &problem->goal;

    int size = problem->size;
    struct TreeNode *root = tree_node_new(&problem->init_state, 0, 0);
    root->depth = 0;
    root->heuristic = get_h(root->state, goal, size);

    list_push(&open_list, root);
    hash_map_found_or_add(visited, root->state, size, root);

    do {
        struct TreeNode *node = list_pop_min(&open_list);
        if (state_is_equal(node->state, goal, size)) {
            fill_result(node, &problem->result);
            break;
        }
        struct TreeNode **child_ptr = tree_node_expand(node, size);
        for (; *child_ptr;) {
            (*child_ptr)->heuristic = (*child_ptr)->depth + get_h((*child_ptr)->state, goal, size);

            struct TreeNode *old_node;
            old_node = hash_map_found_or_add(visited, (*child_ptr)->state, size, node);
            if (old_node) {
                int difference = (*child_ptr)->depth - old_node->depth;
                bool is_shorter = difference < 0;
                if (is_shorter) {
                    delete_child(find_child(old_node->parent->child, old_node));
                    tree_node_delete(*child_ptr, size);
                    old_node->parent = node;
                    tree_update_depth(old_node, difference);
                }
#ifdef REALLY_DELETE_NODES
                delete_child(child_ptr);
#else
                (*child_ptr)->is_deleted = true;
                child_ptr++;
#endif
                continue;
            }
            list_push(&open_list, *child_ptr);
            child_ptr++;
        }
    } while (!list_is_empty(&open_list));
    problem->result.tree = root;
    list_delete(&open_list);
    hash_map_delete(visited);
}
