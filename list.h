#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include "problem.h"

struct ListNode {
    struct TreeNode *value;
    struct ListNode *next;
    struct ListNode *prev;
};

struct List {
    struct ListNode *head;
    struct ListNode *tail;
};

void list_init(struct List *list);

void list_delete(struct List *list);

void list_push(struct List *list, struct TreeNode *value);

struct TreeNode * list_pop_front(struct List *list);

struct TreeNode * list_pop_back(struct List *list);

bool list_is_empty(struct List *list);

#endif
