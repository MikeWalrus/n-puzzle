#include <stddef.h>

#include "list.h"
#include "utilities.h"

void list_init(struct List *list)
{
    list->head = NULL;
    list->tail = NULL;
}

void list_push(struct List *list, struct TreeNode *value)
{
    struct ListNode *new_node = malloc_or_die(sizeof(*new_node));
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = list->tail;
    if (list->head) {
        list->tail->next = new_node;
        list->tail = new_node;
    } else {
        list->tail = new_node;
        list->head = new_node;
    }
}

bool list_is_empty(struct List *list)
{
    return list->head == NULL;
}

struct TreeNode * list_pop_front(struct List *list)
{
    struct ListNode *node = list->head;
    struct TreeNode *ret = node->value;
    list->head = node->next;
    if (list->head)
        node->next->prev = NULL;
    else
        list->tail = NULL;
    free(node);
    return ret;
}

struct TreeNode * list_pop_back(struct List *list)
{
    struct ListNode *node = list->tail;
    struct TreeNode *ret = node->value;
    list->tail = node->prev;
    if (list->tail)
        node->prev->next = NULL;
    else
        list->head = NULL;
    free(node);
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
