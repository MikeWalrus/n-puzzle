#include <stddef.h>

#include "problem.h"

int get_heuristic(struct State *s, struct State *goal, int size)
{
    int ret = 0;
    int **matrix = s->matrix;
    int **matrix_goal = goal->matrix;
    matrix[s->empty_i][s->empty_j] = matrix_goal[goal->empty_i][goal->empty_j];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] != matrix_goal[i][j])
                ret++;
        }
    }
    return ret;
}

void children_delete_others(struct TreeNode **children, struct TreeNode *the_one, int size)
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
    int min_heuristic = root->heuristic = get_heuristic(root->state, &problem->goal, size);
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

            int heuristic = child->heuristic = get_heuristic(child->state, goal, size);
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