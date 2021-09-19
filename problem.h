#ifndef PROBLEM_H
#define PROBLEM_H

#include <stdbool.h>

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

bool matrix_is_equal(int** a, int** b, int size);

bool state_is_equal(struct State *a, struct State *b, int size);

void apply_operation(struct State* state, int size, enum Operation op);

void apply_operations(struct State* state, int size, enum Operation *ops, int ops_size);

void state_init(struct State *state, int size);

void problem_init(struct Problem *p, int size);

#endif
