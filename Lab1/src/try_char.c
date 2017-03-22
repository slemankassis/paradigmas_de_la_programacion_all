#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "try_char.h"

// Funcion que comprueba que el caracter sea un alfanumerico valido
bool valid_char(char c) {
    int i;
    bool result = false;
    char *listchar = "àèìòùáéíóúäëïöüÁÀÉÈÍÌÓÒÚÙÖÜ";

    if ((c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9')) {
        result = true;

    } else {
        for (i = 0; !(result) && i < 27; i++) {
            result = (c == listchar[i]);
        }
    }

    return result;
}

// Funcion que transforma de mayuscula a miscula o minuscula a
// mayuscula segun corresponda
char change_mayus_minus(char c) {
    // a = 61 and z = 122.
    if (c >= 'a' && c <= 'z') {
        c -= 32;
    } else {
        // A = 41 and z = 90. (c >= 'A' && c <= 'Z').
        c += 32;
    }
    return c;
}

// Funcioin retorna true si el caracter leido esta en mayuscula o no
bool is_mayus(char c) {
    return (c >= 'A' && c <= 'Z');
}
