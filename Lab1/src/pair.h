#ifndef _PAIR_H
#define _PAIR_H

#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

#include "index.h"

typedef struct _pair_t *pair_t;

pair_t pair_from_spa_ing(index_t spa, index_t ing);
/*
 Build a new pair from the given index and data using references to them.

 Do NOT free index and data after creating the pair, but only through
 pair_destroy.

 PRE: 'index' and 'data' are not NULL.

 POST: the result is not NULL, and pair_fst(result) is equal to 'index',
 and pair_snd(result) is equal to 'data'.
*/

pair_t pair_destroy(pair_t pair);
/*
 Free the memory allocated by the given 'pair', as well as the respective
 index and data. Set 'pair' to NULL.
*/

index_t pair_fst(pair_t pair);
/*
 Return a reference to the first pair element.

 PRE: 'pair' is not NULL.

 POST: the result is not NULL, and should never be freed by the caller.
*/

index_t pair_snd(pair_t pair);
/*
 Return a reference to the second pair element.

 PRE: 'pair' is not NULL.

 POST: the result is not NULL, and should never be freed by the caller.
*/

#endif
