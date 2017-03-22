#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "index.h"
#include "pair.h"

struct _pair_t {
    index_t spa;
    index_t ing;
};

pair_t pair_from_spa_ing(index_t spa, index_t ing) {
    pair_t p = NULL;

    assert(spa != NULL);
    assert(ing != NULL);

    p = calloc(1, sizeof(struct _pair_t));
    p->spa = spa;
    p->ing = ing;

    assert(index_is_equal(pair_fst(p), spa));
    assert(index_is_equal(pair_snd(p), ing));

    spa = NULL;
    ing = NULL;

    return p;
}

pair_t pair_destroy(pair_t pair) {
    assert(pair != NULL);

    if (pair->spa != NULL) {
        pair->spa = index_destroy(pair->spa);
    }

    if (pair->ing != NULL) {
        pair->ing = index_destroy(pair->ing);
    }

    free(pair);
    pair = NULL;

    return pair;
}

index_t pair_fst(pair_t pair) {
    index_t result = NULL;
    assert(pair != NULL);
    result = (pair->spa);
    assert(result != NULL);
    return (result);
}

index_t pair_snd(pair_t pair) {
    index_t result = NULL;
    assert(pair != NULL);
    result = (pair->ing);
    assert(result != NULL);
    return (result);
}
