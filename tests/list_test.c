#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../list.h"
#include "../problem.h"

#define GREEN   "\x1b[32m"

void push_0_to_99(struct List *list)
{
    struct TreeNode *tmp;
    for (int i = 0; i < 100; i++) {
        tmp = malloc(sizeof(*tmp));
        tmp->step = i;
        tmp->heuristic = i;
        list_push(list, tmp);
    }
}

int main(int argc, char **argv)
{
    struct List list;
    list_init(&list);
    assert(list_is_empty(&list));

    struct TreeNode node = {.op = 1};
    list_push(&list, &node);
    assert(!list_is_empty(&list));

    struct TreeNode *tmp;
    tmp = list_pop_back(&list);
    assert(tmp->op == 1);
    assert(list_is_empty(&list));

    push_0_to_99(&list);

    for (int i = 0; i < 100; i++) {
        tmp = list_pop_front(&list);
        assert(tmp->step == i);
    }

    push_0_to_99(&list);

    for (int i = 99; i >= 0; i--) {
        tmp = list_pop_back(&list);
        assert(tmp->step == i);
    }

    push_0_to_99(&list);
    assert(list_pop_min(&list)->heuristic == 0);

    tmp = malloc(sizeof(*tmp));
    tmp->heuristic = -100;
    list_push(&list, tmp);
    assert(list_pop_min(&list)->heuristic == -100);


    
    list_delete(&list);

    printf(GREEN"%s: All tests passed.\n", argv[0]);
}
