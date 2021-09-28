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
