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

void swap(int *a, int*b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
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

    swap(&(matrix[state->empty_i][state->empty_j]), &(matrix[new_i][new_j]));
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

int main(void)
{
    Solution s = solve;
    char *str = readline("Size: ");
    char *end;
    int size = strtol(str, &end, 10);
    if (str == end)
        die("%s is not a number.", str);
    return 0;
}
