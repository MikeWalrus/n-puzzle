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
    if (!matrix_is_equal(m_a, m_b, size))
        return false;
    return true;
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

void problem_init(struct Problem *p, int size)
{
    p->size = size;
    state_init(&p->init_state, size);
    state_init(&p->goal, size);
    p->result.op_size = 0;
    p->result.op = NULL;
}

