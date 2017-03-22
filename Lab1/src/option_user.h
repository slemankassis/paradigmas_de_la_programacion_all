#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dict.h"

/*
Funcion que traduce o no, una palabra segun una opcion del usuario, y
agrega una palabra nueva a un diccionario determinado segund corresponda
la funcion recibe 4 argunmentos, dict que es diccionario ingresado
por el usuario, temp diccionario de palabras nuevas pero que no se guarda,
dict_ignore lista de palabras ignoradas y buff, la palabra que se desea
traducir
*/

char * word_user(dict_t dict, dict_t temp, dict_t dict_ignore, char *buffchar);
