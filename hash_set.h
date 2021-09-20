#ifndef HASH_SET_H
#define HASH_SET_H

#include <stdbool.h>

#define HASH_SET_SIZE 2048

struct HashSetNode {
    struct State *key;
    struct HashSetNode *next;
};

struct HashSet {
    struct HashSetNode heads[HASH_SET_SIZE];
};

struct HashSet * hash_set_new(void);

bool hash_set_found_or_add(struct HashSet *hash_set, struct State *state, int size);

#endif
