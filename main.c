#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>

#include "utilities.h"

struct State {
    int ** matrix;
    int empty_i;
    int empty_j;
};

enum Operation {
    up, down, left, right
};

struct Node {
    struct State *state;
    enum Operation op;
    struct Node *child[4];
    int step;
};

struct Result {
    enum Operation *op;
    int op_size;
    struct Node *tree;
};

struct Problem {
    int size;
    struct State init_state;
    struct State goal;
    struct Result result;
};

typedef void (*Solution)(struct Problem *problem);

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

void solve(struct Problem *problem)
{
}

void check_size(int size)
{
    if (size <= 1)
        die("%d is an invalid size.", size);
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

int str_to_int(char **str, const char *msg)
{
    const char *begin = *str;
    int num = strtol(begin, str, 10);
    if (begin == *str)
        die("\"%s\" %s", begin, msg);
    return num;
}

void check_unoccupied(struct State *state, int size)
{
    int i = state->empty_i;
    int j = state->empty_j;
    if (i < 0 || i >= size || j < 0 || j >= size)
        die("(%d, %d) is out of bound. size = %d", i, j, size);
}

void read_state(int size, struct State *state, const char *prompt)
{
    char *str;

    for (int i = 0; i < size; i++) {
        str = readline(prompt);
        for (int j = 0; j < size; j++) {
            int num = str_to_int(&str, "is invalid. Expect more integers.");
            state->matrix[i][j] = num;
        }
        if (*str)
            printf("\"%s\" is ignored.\n", str);
    }

    str = readline("Unoccupied position i j: ");
    state->empty_i = str_to_int(&str, "is invalid. Expect 2 integers");
    state->empty_j = str_to_int(&str, "is invalid. Expect 2 integers");
    check_unoccupied(state, size);
}

int main(void)
{
    Solution s = solve;
    char *str;
    char *end;

    str = readline("Size: ");
    int size = strtol(str, &end, 10);
    if (str == end)
        die("\"%s\" is not a number.", str);
    check_size(size);

    struct Problem problem;
    problem_init(&problem, size);
    read_state(size, &(problem.init_state), "Initial state: ");
    read_state(size, &(problem.goal), "Goal: ");

    s(&problem);

    struct Result *result = &problem.result;
    apply_operations(&problem.init_state, size, result->op, result->op_size);
    if (!state_is_equal(&problem.init_state, &problem.goal, size))
        die("Not solved.");

    return 0;
}
