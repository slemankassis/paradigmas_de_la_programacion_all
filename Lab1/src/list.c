#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list.h"
#include "index.h"
#include "pair.h"


struct _node_t {
    list_t next;
    pair_t pair;
};

list_t list_empty(void) {
    list_t list = NULL;

    return list;
}

list_t list_destroy(list_t list) {

    list_t aux1 = NULL;
    list_t aux2 = NULL;

    if (list != NULL) {
        aux1 = list;
        while (aux1 != NULL) {
            aux2 = aux1->next;
            aux1->pair = pair_destroy(aux1->pair);
            free(aux1);
            aux1 = aux2;
        }
        aux1 = NULL;
        aux2 = NULL;
    }
    return list;
}

index_t list_search(list_t list, index_t index, bool is_reverse) {
    index_t result = NULL;

    if (list != NULL) {
        bool is_searching = true;
        index_t index_search = NULL;
        list_t _list = list;

        while (is_searching && _list != NULL) {
            // Searching from Spanish to English.
            if (!is_reverse) {
            index_search = pair_fst(_list->pair);

                if (index_is_equal(index, index_search)) {
                    result = pair_snd(_list->pair);
                    is_searching = false;
                }
            // Searching from English to Spanish.
            } else {
                index_search = pair_snd(_list->pair);

                if (index_is_equal(index, index_search)) {
                    result = pair_fst(_list->pair);
                    is_searching = false;
                }
            }

            _list = _list->next;
        }

        index_search = NULL;
        _list = NULL;
    }
    return result;
}

list_t list_append(list_t list, index_t w_spa, index_t w_ing) {
    list_t new = list_empty();

    new = calloc(1, sizeof(struct _node_t));
    new->next = NULL;
    new->pair = pair_from_spa_ing(w_spa, w_ing);

    if (list != NULL) {
        list_t last = list;

        while (last->next != NULL) {
            last = last->next;
        }

        last->next = new;

        new = NULL;
        last = NULL;

    } else {
        list = new;
    }

    w_spa = NULL;
    w_ing = NULL;

    return list;
}

void list_dump(list_t list, FILE * fd) {
    if (list != NULL) {
        list_t aux = list;

        while (aux != NULL) {
            char *w_spa = index_to_string(pair_fst(aux->pair));
            char *w_ing = index_to_string(pair_snd(aux->pair));

            fprintf(fd, "%s,%s\n", w_spa, w_ing);
            aux = aux->next;

            free(w_spa);
            w_spa = NULL;

            free(w_ing);
            w_ing = NULL;
        }
    }
}
