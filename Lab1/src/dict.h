#ifndef _DICT_H
#define _DICT_H

#define SIZE_BUFF 1024

#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "index.h"

typedef char *word_t;
typedef char *def_t;
typedef struct _dict_t *dict_t;

dict_t dict_empty(void);
/*
 Return a newly created, empty dictionary.

 The caller must call dict_destroy when done using the resulting dict,
 so the resources allocated by this call are freed.

 POST: the result is not NULL, and dict_length(result) is 0.
*/

dict_t dict_destroy(dict_t dict);
// Free the resources allocated for the given 'dict', and set it to NULL.

bool dict_is_reverse(dict_t dict);
// Return if dict is reverse.

dict_t dict_reverse_change(dict_t dict);
// Change language of translation.

bool dict_exists(dict_t dict, word_t word);
/*
 Return if the given 'word' exists in the dictionary 'dict'.

 PRE: 'dict' and 'word' are not NULL.
*/

def_t dict_search(dict_t dict, word_t word);
// Returns the definition corresponding to the word entered.

dict_t dict_add(dict_t dict, word_t word, def_t def);
// Add a word to the dictionary and his translation.

void dict_dump(dict_t dict, FILE * fd);
/*
 Dump the given 'dict' in the given file descriptor 'fd'.

 PRE: 'dict' is not NULL, and 'fd' is a valid file descriptor.
*/

dict_t dict_data_system();
/*
crea y carga un diccionario por defecto ya establecido en la memoria
*/

def_t dict_search_ing(dict_t dict, word_t word);
#endif
