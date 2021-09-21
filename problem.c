#include <stddef.h>
#include "utilities.h"
#include "problem.h"

bool matrix_is_equal(int** a, int** b, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (a[i][j] != b[i][j])
                return false;
    return true;
}

bool state_is_equal(struct State *a, struct State *b, int size)
{
    int **m_a = a->matrix;
    int **m_b = b->matrix;
    int a_i = a->empty_i;
    int a_j = a->empty_j;
    int b_i = b->empty_i;
    int b_j = b->empty_j;

    if (a_i != b_i || a_j != b_j)
        return false;
    m_a[a_i][a_j] = m_b[b_i][b_j];
    return matrix_is_equal(m_a, m_b, size);
}

void apply_operation(struct State* state, int size, enum Operation op)
{
    int i = 0;
    int j = 0;

    switch (op) {
        case (up):
            i = -1;
            break;
        case (down):
            i = 1;
            break;
        case (left):
            j = -1;
            break;
        case (right):
            j = 1;
            break;
    }
    int new_i = state->empty_i + i;
    int new_j = state->empty_j + j;
    int** matrix = state->matrix;

    matrix[state->empty_i][state->empty_j] = matrix[new_i][new_j];
    state->empty_i = new_i;
    state->empty_j = new_j;
}

void apply_operations(struct State* state, int size, enum Operation *ops, int ops_size)
{
    for (int i = 0; i < ops_size; i++) {
        apply_operation(state, size, ops[i]);
    }
}

void state_init(struct State *state, int size)
{
    state->matrix = malloc_or_die(size * sizeof(*(state->matrix)));
    for (int i = 0; i < size; i++) {
        state->matrix[i] = malloc_or_die(size * sizeof(*(state->matrix[0])));
    }
}

struct State * state_copy(const struct State *state, int size)
{
    struct State *ret = malloc(sizeof(*ret));
    int **matrix;
    int **old_matrix = state->matrix;
    matrix = malloc_or_die(size * sizeof(*(matrix)));
    for (int i = 0; i < size; i++) {
        matrix[i] = malloc_or_die(size * sizeof(*(matrix[0])));
        for (int j = 0; j < size; j++)
            matrix[i][j] = old_matrix[i][j];
    }
    ret->matrix = matrix;
    ret->empty_i = state->empty_i;
    ret->empty_j = state->empty_j;
    return ret;
}

struct State * state_copy_and_apply(const struct State *state, int size, enum Operation op)
{
    struct State *ret = state_copy(state, size);
    apply_operation(ret, size, op);
    return ret;
}

void state_delete(struct State *state, int size)
{
    int** matrix = state->matrix;
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void problem_init(struct Problem *p, int size)
{
    p->size = size;
    state_init(&p->init_state, size);
    state_init(&p->goal, size);
    p->result.op_size = 0;
    p->result.ops = NULL;
}

struct TreeNode * tree_node_new(struct State *state, enum Operation op, int step)
{
    struct TreeNode *ret = malloc_or_die(sizeof(*ret));
    ret->state = state;
    ret->op = op;
    ret->step = step;
    return ret;
}

bool is_applicable(const struct State *state, int size, enum Operation op)
{
    switch (op) {
        case (up):
            return state->empty_i != 0;
        case (down):
            return state->empty_i + 1 != size;
        case (left):
            return state->empty_j != 0;
        case (right):
            return state->empty_j + 1 != size;
    }
    return false;
}

struct TreeNode ** tree_node_expand(struct TreeNode *node, int size)
{
    struct TreeNode **last_child = node->child;
    struct State *state = node->state;
    int step = node->step + 1;
    for (int op = 0; op < 4; op++) {
        if (is_applicable(state, size, op)) {
            struct State *new_state = state_copy_and_apply(state, size, op);
            struct TreeNode *new_child = tree_node_new(new_state, op, step);
            new_child->parent = node;
            *(last_child++) = new_child;
        }
    }
    *last_child = NULL;
    return node->child;
}

void fill_result(struct TreeNode *node, struct Result *result)
{
    int op_size = result->op_size = node->step;
    enum Operation *ops = result->ops = malloc_or_die(op_size * sizeof(*ops));
    for (int i = op_size - 1; i >= 0; i--) {
        ops[i] = node->op;
        node = node->parent;
    }
}

