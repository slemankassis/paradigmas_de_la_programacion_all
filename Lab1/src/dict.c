#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "dict.h"
#include "helpers.h"
#include "index.h"
#include "list.h"

struct _dict_t {
    list_t list;
    bool is_reverse;
};

dict_t dict_empty(void) {
    dict_t dict = calloc(1, sizeof(struct _dict_t));
    dict->list = NULL;
    dict->is_reverse = false;
    return dict;
}

dict_t dict_reverse_change(dict_t dict) {
    assert(dict != NULL);

    dict->is_reverse = !(dict->is_reverse);

    return dict;
}

bool dict_is_reverse(dict_t dict) {
    return dict->is_reverse;
}

dict_t dict_destroy(dict_t dict) {
    assert(dict != NULL);

    dict->list = list_destroy(dict->list);
    free(dict);
    dict = NULL;
    return dict;
}

bool dict_exists(dict_t dict, word_t word) {
    assert(dict != NULL);
    assert(word != NULL);
    bool exists = false;
    index_t index = index_from_string(word);
    index_t index_2 = list_search(dict->list, index, dict->is_reverse);

    if (index_2 != NULL) {
        exists = true;
    }

    index_destroy(index);
    word = NULL;
    return exists;
}

def_t dict_search(dict_t dict, word_t word) {
    assert(dict != NULL);
    assert(word != NULL);
    def_t definition = NULL;
    index_t indaux = index_from_string(word);

    if (dict_exists(dict, word)) {
        definition = index_to_string(list_search(dict->list,
                                                    indaux, dict->is_reverse));
    }

    index_destroy(indaux);
    word = NULL;
    return definition;
}

dict_t dict_add(dict_t dict, word_t word, def_t def) {
    assert(dict != NULL);
    assert(word != NULL);
    assert(def != NULL);

    if (dict_exists(dict, word) == false) {
        index_t auxt = index_from_string(word);
        index_t auxd = index_from_string(def);

        dict->list = list_append(dict->list, auxt, auxd);
    }
    word = NULL;
    def = NULL;
    return dict;
}

void dict_dump(dict_t dict, FILE *fd) {
    assert(dict != NULL);
    assert(fd != NULL);

    list_dump(dict->list, fd);

    fd = NULL;
}

dict_t dict_data_system() {

    dict_t dict = dict_empty();

    int i = 0;

    char *data[92] = {"tiempo","time","cosa","thing","mundo","world","parte",
    "portion","vida","life","año","year","dia","day","hombre","man","mujer",
    "woman","cómo","as","estas","these","casa","home","cocina","kitchen",
    "sol","sun","luna","moon","feliz","happy","otro","other","cada","each",
    "ahora","now","gobierno","government","duraten","during","siempre","alway",
    "pais","country","menos","lees","forma","form","caso","case","nada",
    "nothing","hacer","do","general","general","estaba","was","estos","these",
    "algo","something","hacia","to","ayer","yesterday","primero","first",
    "lugar","place","mientras","while","trabajo","work","casi","almost",
    "poder","power","tiene","have","frente","front","historia","history",
    "dentro","within","punto","point","cualquier","any"};

    while (i <= 90) {

        dict = dict_add(dict, data[i], data[i+1]);
        i = i + 2;
    }

    return dict;
}
