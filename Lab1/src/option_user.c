#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"
#include "helpers.h"
#include "option_user.h"

/* Funcion que comprueba que el argunmento para elegir la opcion
sea del formato correcto*/
char print_option() {
    char result = '\0', discard = '\0';
    int scanf_result = 0;

    scanf_result = scanf("%c", &result);

    if (scanf_result != 1) {
        result = '\0';
    }

    // Consume everything left in the stdin buffer.
    while (discard != '\n') {
        scanf_result = scanf("%c", &discard);
    }

    return (result);
}

/* Funcion que hace un intercambio entre dos variables de "string" */
void swap_char(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

/* Funcion que traduce una palabra o no, segun la opcion dada, la
funcion, recibe 4 argunmentos, dict que es diccionario ingresado
por el usuario, temp diccionario de palabras nuevas pero que no se guarda,
dict_ignore lista de palabras ignoradas y buff, la palabra que se desea
traducir*/

char * word_user(dict_t dict, dict_t dict_temp,
                 dict_t dict_ignored, char *buff) {
    char *buff_translated = calloc(SIZE_BUFF, sizeof(char));
    char option;
    bool state = true;
    
    while (state) {
        option = print_option();
        switch (option) {
            case 'i':  // "Ignorar".
                // It is decided to pass the word untranslated.
                buff_translated = buff;
                state = false;
                break;

            case 'h':  // "Ignorar todas".
                // It is added to list of ignored words.
                dict_add(dict_ignored, buff, buff);
                buff_translated = buff;
                state = false;
                break;

            case 't':  // Traducir como".
                // It is added to temporary list, only for current file.
                printf("Traducir: %s como: ", buff);
                buff_translated = readline_from_stdin();

                if (dict_is_reverse(dict)) {
                    swap_char(&buff_translated, &buff);
                }

                dict_add(dict_temp, buff, buff_translated);
                state = false;
                break;

            case 's':  // "Traducir siempre como".
                // It is added to the open dict.
                printf("Traducir: %s como: ", buff);
                buff_translated = readline_from_stdin();

                if (dict_is_reverse(dict)) {
                    swap_char(&buff_translated, &buff);
                }

                dict_add(dict, buff, buff_translated);
                state = false;
                break;

            default:
                printf("\n\"%c\" is invalid. Please choose a valid option."
                       "\n\n", option);
        }
    }
    return buff_translated;
}
