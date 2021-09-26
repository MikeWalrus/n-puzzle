#include <stddef.h>

#include "list.h"
#include "utilities.h"

void list_init(struct List *list)
{
    list->head = malloc_or_die(sizeof(*list->head));
    list->tail = malloc_or_die(sizeof(*list->tail));
    list->head->next = list->tail;
    list->tail->prev = list->head;
    list->head->prev = NULL;
    list->tail->next = NULL;
}

void list_push(struct List *list, struct TreeNode *value)
{
    struct ListNode *new_node = malloc_or_die(sizeof(*new_node));
    new_node->value = value;
    struct ListNode *prev = list->tail->prev;
    prev->next = new_node;
    new_node->prev = prev;
    new_node->next = list->tail;
    list->tail->prev = new_node;
}

bool list_is_empty(struct List *list)
{
    return list->head->next == list->tail; 
}

struct TreeNode * list_pop_front(struct List *list)
{
    struct ListNode *node = list->head->next;
    struct TreeNode *ret = node->value;
    list->head->next = node->next;
    node->next->prev = list->head;
    free(node);
    return ret;
}

struct TreeNode * list_pop_back(struct List *list)
{
    struct ListNode *node = list->tail->prev;
    struct TreeNode *ret = node->value;
    list->tail->prev = node->prev;
    node->prev->next = list->tail;
    free(node);
    return ret;
}

struct TreeNode * list_pop_min(struct List *list)
{
    struct ListNode *min_node = list->head->next;
    int min = min_node->value->heuristic;
    for (struct ListNode *p = min_node->next; p != list->tail; p = p->next) {
        int heuristic = p->value->heuristic;
        if (heuristic < min) {
            min = heuristic;
            min_node = p;
        }
    }
    min_node->prev->next = min_node->next;
    min_node->next->prev = min_node->prev;
    struct TreeNode *ret = min_node->value;
    free(min_node);
    return ret;
}

void list_delete(struct List *list)
{
    struct ListNode *ptr = list->head;
    while (ptr) {
        struct ListNode *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
}
