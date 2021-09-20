#include "problem.h"
#include "utilities.h"
#include "hash_set.h"

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
        if (state_is_equal(ptr->key, state, size))
            return true;
        ptr = ptr->next;
    }
    ptr = ptr->next = malloc_or_die(sizeof(*(ptr->next)));
    ptr->key = state;
    ptr->next = NULL;
    return false;
}
