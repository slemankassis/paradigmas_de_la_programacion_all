#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "index.h"
#include "pair.h"

typedef struct _node_t *list_t;

list_t list_empty(void);
/*
 Return a newly created, empty list.

 The caller must call list_destroy when done using the resulting list,
 so the resources allocated by this call are freed.

 POST: the result is a valid list pointer, and list_length(result) is 0.
*/

list_t list_destroy(list_t list);
// Free the resources allocated for the given 'list', and set it to NULL.

index_t list_search(list_t list, index_t index, bool is_reverse);
/*
 Return the data associated to the given 'index' in the given 'list',
 or NULL if the 'index' is not in 'list'.

 The caller must NOT free the resources allocated for the result when done
 using it.

 PRE: 'list' and 'index' are valid instances.

 POST: the result is NULL, or not NULL and should not be destroyed.
*/

list_t list_append(list_t list, index_t index, index_t data);
/*
 Return the given 'list' with the ('index', 'data') added to the end.

 The given 'index' and 'data' are inserted in the list,
 so they can not be destroyed by the caller.

 PRE: all 'list', 'index' and 'data' are valid instances.

 POST: the length of the result is the same as the length of 'list'
 plus one. The elements of the result are the same as the ones in 'list'
 with the new pair ('index', 'data') added at the end of the list.

 In order words, using pseudo code, the POST is:
 (list_length(list) + 1 == list_length(result)) and
 (forall i: 0 <= i < list_length(list): list[i] == result[i]) and
 (result[list_length(list)] == ('index', 'data')
*/

void list_dump(list_t list, FILE * fd);
/*
 Dump the list elements using their string representation to the given
 file descriptor.

 PRE: 'list' is a valid list pointer, and 'fd' is a valid file descriptor.
*/

#endif
