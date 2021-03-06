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

#ifndef HASH_SET_H
#define HASH_SET_H

#include <stdbool.h>

#define HASH_SET_SIZE 1048576

struct HashSetNode {
    struct State *key;
    struct HashSetNode *next;
};

struct HashSet {
    struct HashSetNode heads[HASH_SET_SIZE];
};

struct HashSet * hash_set_new(void);

bool hash_set_found_or_add(struct HashSet *hash_set, struct State *state, int size);

void hash_set_delete(struct HashSet *hashmap);

#define HASH_MAP_SIZE 1048576

struct HashMapNode {
    struct State *key;
    struct TreeNode *value;
    struct HashMapNode *next;
};

struct HashMap {
    struct HashMapNode heads[HASH_SET_SIZE];
};

struct HashMap * hash_map_new(void);

void hash_map_delete(struct HashMap *hashmap);

struct TreeNode * hash_map_found_or_add(struct HashMap *hash_map, struct State *state, int size, struct TreeNode *value);

#endif
