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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <readline/readline.h>

#include "utilities.h"
#include "problem.h"
#include "solutions.h"
#include "visual.h"

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

void read_problem(struct Problem *problem)
{
    char *str;
    char *end;

    str = readline("Size: ");
    int size = strtol(str, &end, 10);
    if (str == end)
        die("\"%s\" is not a number.", str);
    check_size(size);

    problem_init(problem, size);
    read_state(size, &(problem->init_state), "Initial state: ");
    read_state(size, &(problem->goal), "Goal: ");
}

void print_ops(enum Operation *ops, int op_size)
{
    for (int i = 0; i < op_size; i++)
        printf("%s ", get_op_emoji(ops[i]));
    printf("\n");
}

bool has_solved(struct Problem *problem)
{
    int size = problem->size;
    struct Result *result = &problem->result;
    apply_operations(&problem->init_state, size, result->ops, result->op_size);
    return state_is_equal(&problem->init_state, &problem->goal, size);
}

char * get_algorithm_names(void)
{
    int len = 1;
    for (int i = 0; i < sizeof(algorithms) / sizeof(algorithms[0]); i++) {
        len += strlen(algorithms[i].name) + 1;
    }
    char *ret = malloc(len);
    ret[0] = 0;
    for (int i = 0; i < sizeof(algorithms) / sizeof(algorithms[0]); i++) {
        strcat(ret, algorithms[i].name);
        strcat(ret, "/");
    }
    ret[len - 2] = 0;
    return ret;
}

void usage(const char *program)
{
    char *names = get_algorithm_names();
    printf("usage: %s [-a %s] [-o output_file]  [-h]", program, names);
    exit(1);
}

Solution get_algorithm(const char *name)
{
    for (int i = 0; i < sizeof(algorithms) / sizeof(algorithms[0]); i++) {
        if (!strcmp(name, algorithms[i].name))
            return algorithms[i].solution;
    }
    die("No such algorithm: %s", name);
    return NULL;
}

void check_arg_param(int i, int argc, const char *program)
{
    if (i + 1 >= argc)
        usage(program);
}

int main(int argc, char **argv)
{
    Solution solve = algorithms[0].solution;
    const char *output_file = NULL;
    const char *program = argv[0];

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h"))
            usage(program);
        else if (!strcmp(argv[i], "-a")) {
            check_arg_param(i, argc, program);
            solve = get_algorithm(argv[++i]);
        } else if (!strcmp(argv[i], "-o")){
            check_arg_param(i, argc, program);
            output_file = argv[++i];
        }
    }

    struct Problem problem;
    read_problem(&problem);

    solve(&problem);

    if (!has_solved(&problem))
        fprintf(stderr, "Not solved.\n");

    struct Result *result = &problem.result;
    print_ops(result->ops, result->op_size);
    if (output_file)
        generate_dot(result->tree, problem.size, output_file);

    return 0;
}
