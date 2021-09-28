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

struct TreeNode * list_pop_min(struct List *list);

bool list_is_empty(struct List *list);

#endif
