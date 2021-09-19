#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>

#include "utilities.h"
#include "problem.h"
#include "solutions.h"

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

void check_size(int size)
{
    if (size <= 1)
        die("%d is an invalid size.", size);
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
    Solution s = solve_bfs;
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
