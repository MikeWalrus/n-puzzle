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

#include "problem.h"
#include "utilities.h"
#include "hash_set.h"

#include <stdio.h>

struct HashSet * hash_set_new(void)
{
    struct HashSet *ret = malloc_or_die(sizeof(*ret));
    struct HashSetNode *heads = ret->heads;
    for (int i = 0; i < HASH_SET_SIZE; i++) {
        heads[i].next = NULL;
    }
    return ret;
}

void hash_set_delete(struct HashSet *hashmap)
{
    for (int i = 0; i < HASH_SET_SIZE; i++) {
        struct HashSetNode *node = hashmap->heads[i].next;
        while (node) {
            struct HashSetNode *delete_this = node;
            node = node->next;
            free(delete_this);
        }
    }
}

int hash_state(struct State *state, int size)
{
    int** matrix = state->matrix;
    matrix[state->empty_i][state->empty_j] = 0;
    int hash = 0;
    int size_cubic = size * size;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            hash = (hash * size_cubic + matrix[i][j]) % HASH_SET_SIZE;
        }
    }

    return hash;
}

bool hash_set_found_or_add(struct HashSet *hash_set, struct State *state, int size)
{
    int hash = hash_state(state, size);
    struct HashSetNode *ptr = &hash_set->heads[hash];
    while (ptr->next) {
        if (state_is_equal(ptr->next->key, state, size)) {
            return true;
        }
        ptr = ptr->next;
    }
    ptr = ptr->next = malloc_or_die(sizeof(*(ptr->next)));
    ptr->key = state;
    ptr->next = NULL;
    return false;
}

struct HashMap * hash_map_new(void)
{
    struct HashMap *ret = malloc_or_die(sizeof(*ret));
    struct HashMapNode *heads = ret->heads;
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        heads[i].next = NULL;
    }
    return ret;
}

void hash_map_delete(struct HashMap *hashmap)
{
    for (int i = 0; i < HASH_SET_SIZE; i++) {
        struct HashMapNode *node = hashmap->heads[i].next;
        while (node) {
            struct HashMapNode *delete_this = node;
            node = node->next;
            free(delete_this);
        }
    }
}

struct TreeNode * hash_map_found_or_add(struct HashMap *hash_map, struct State *state, int size, struct TreeNode *value)
{
    int hash = hash_state(state, size);
    struct HashMapNode *ptr = &hash_map->heads[hash];
    while (ptr->next) {
        if (state_is_equal(ptr->next->key, state, size)) {
            return ptr->next->value;
        }
        ptr = ptr->next;
    }
    ptr = ptr->next = malloc_or_die(sizeof(*(ptr->next)));
    ptr->key = state;
    ptr->value = value;
    ptr->next = NULL;
    return false;
}
