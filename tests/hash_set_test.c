#include <assert.h>
#include "../problem.h"
#include "../hash_set.h"

int main(int argc, char **argv)
{
    struct HashSet *h = hash_set_new();
    struct State state;
    state.empty_i = 0;
    state.empty_j = 0;
    state_init(&state, 3);
    hash_set_found_or_add(h, &state, 3);
    assert(hash_set_found_or_add(h, &state, 3));
}
