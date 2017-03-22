#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"
#include "dict_helpers.h"
#include "try_char.h"
#include "translate.h"
#include "option_user.h"

void translate(dict_t dict, dict_t dict_temp, dict_t dict_ignored,
               char *file_input, char *file_output, char *file_ignored) {
    assert(dict != NULL);
    assert(file_input != NULL);

    int i;
    char c = '\0';
    bool flag_mayus;

    dict_t dict_system = dict_data_system();

    FILE *file;
    FILE *out;
    FILE *ignored;

    char *buff = calloc(SIZE_BUFF, sizeof(char));
    char *buff_translated = calloc(SIZE_BUFF, sizeof(char));

    file = fopen(file_input, "r");
    out = fopen(file_output, "w");
    ignored = fopen(file_ignored, "w");

    if (file == NULL) {
        printf("input_file == NULL, exit\n");
        goto exit_program;
    }

    // Changes characteristics words (accents and capital letters).
    while (!feof(file)) {
        c = fgetc(file);
        flag_mayus = false;

        for (i = 0; valid_char(c) && i < 100; i++) {
            if (i == 0) {
                if (is_mayus(c)) {
                    c = change_mayus_minus(c);
                    flag_mayus = true;
                }
            }

            if (is_mayus(c)) {
                c = change_mayus_minus(c);
            }

            buff[i] = c;
            c = fgetc(file);
        }

        // Enter the word in the file, clears the buffer.
        if (i > 0) {
            buff_translated = dict_search(dict, buff);
            if (buff_translated == NULL) {
                buff_translated = dict_search(dict_system, buff);
            }

            // Searching in the dictionary input.
            if (buff_translated == NULL) {
                buff_translated = dict_search(dict_temp, buff);

                // Searching in the list of words ignored.
                if (buff_translated == NULL) {
                    buff_translated = dict_search(dict_ignored, buff);

                    // Ask the user for a translation, gives options.
                    if (buff_translated == NULL) {
                        printf("No hay traducción para la palabra: %s\n",
                                buff);
                        printf("Ignorar (i) - "\
                               "Ignorar todas (h) - "\
                               "Traducir como (t) - "\
                               "Traducir siempre como (s)\n:");
                        buff_translated = word_user(dict, dict_temp,
                                                    dict_ignored, buff);
                    }
                }
            }

            if (flag_mayus && valid_char(buff_translated[0])) {
                buff_translated[0] = change_mayus_minus(buff_translated[0]);
            }

            fprintf(out, "%s", buff_translated);

            memset(buff, 0, SIZE_BUFF*sizeof(char));
            buff_translated = NULL;
        }

        // Write the non-alphanumeric character.
        if (!(valid_char(c)) && !feof(file)) {
            fprintf(out, "%c", c);
        }
    }

    // End of program.
    exit_program:

    dict_dump(dict_ignored, ignored);

    fclose(file);
    fclose(ignored);
    fclose(out);

    free(buff_translated);
    free(buff);

    dict_system = dict_destroy(dict_system);
    dict_system = NULL;
    file = NULL;
    ignored = NULL;
    out = NULL;
}
