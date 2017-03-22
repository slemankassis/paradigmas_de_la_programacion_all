#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"
#include "dict_helpers.h"
#include "helpers.h"
#include "list.h"

dict_t dict_from_file(char *filename) {
    word_t word = NULL;
    def_t def = NULL;
    dict_t result = NULL;
    FILE *fd = NULL;
    char *line = NULL;

    fd = fopen(filename, "a+");

    if (fd != NULL) {
        // Filename is a existing file, so create the empty dict.
        result = dict_empty();
        while (!feof(fd)) {
            line = readline(fd);
            if (line == NULL) {
                // This is the case of the last (empty) line.
                continue;
            }
            word = strtok(line, ",");
            if (word != NULL) {
                def = strtok(NULL, "\n");
                if (def != NULL) {
                    // Remove extra initial spaces, if any.
                    while (def[0] == ' ') {
                        def = def + 1;
                    }
                    result = dict_add(result, word, def);
                }
            }
            free(line);
        }
        fclose(fd);
    }
    return (result);
}


void dict_to_file(dict_t dict, char *filename) {
    FILE *fd = NULL;

    fd = fopen(filename, "w");
    if (fd != NULL) {
        dict_dump(dict, fd);
        fclose(fd);
    }
}
