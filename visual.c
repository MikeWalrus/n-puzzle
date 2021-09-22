#include <stdio.h>

#include "visual.h"
#include "utilities.h"
#include "problem.h"
#include "list.h"

const char * get_op_emoji(enum Operation op)
{
    char *emoji;
    switch (op) {
        case (up):
            emoji = "⬆️";
            break;
        case (down):
            emoji = "⬇️";
            break;
        case (left):
            emoji = "⬅️";
            break;
        case (right):
            emoji = "➡️";
            break;
    }
    return emoji;
}

void fprint_state(FILE *fp, struct State *state, int size)
{
    int** matrix = state->matrix;
    fprintf(fp, "[label=<<table>");
    int empty_i = state->empty_i;
    int empty_j = state->empty_j;
    for (int i = 0; i < size; i++) {
        fprintf(fp, "<tr>");
        for (int j = 0; j < size; j++) {
            if (empty_i == i && empty_j == j)
                fprintf(fp, "<td></td>");
            else
                fprintf(fp, "<td>%d</td>", matrix[i][j]);
        }
        fprintf(fp, "</tr>");
    }
    fprintf(fp, "</table>>]\n");
}

void generate_dot(struct TreeNode *root, int size)
{
    const char *filename = "tree.dot";
    FILE *fp = fopen(filename, "w");
    if (!fp)
        die("Can't open file: %s.", filename);

    fprintf(fp, "digraph Tree {\n");
    fprintf(fp, "\tnode [shape=plaintext]\n");
    struct List list;
    list_init(&list);

    list_push(&list, root);
    do {
        struct TreeNode *node = list_pop_front(&list);

        fprintf(fp, "\t%d\n", node->step);
        fprint_state(fp, node->state, size);
        if (node->parent) {
            fprintf(fp, "\t%d -> %d [headlabel=\"%s\" labelangle=70 labelfontsize=10]\n", node->parent->step, node->step, get_op_emoji(node->op));
        }

        struct TreeNode **childs = &node->child[0];
        for (; *childs; childs++) {
            struct TreeNode *child = *childs;
            list_push(&list, child);
        }

    } while (!list_is_empty(&list));


    fprintf(fp, "}\n");

    fclose(fp);
}
