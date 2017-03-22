#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"

/*
Funcion que traduce un archivo ingresado por el usuario y guarda la
traduccion en un archivo de salida, la funcion recibe un diccionario
ingresado por el usario, un dicc. temporal para palabras que no seran
guardadas, un dicc. ignore que es una lista de palabras que se ignoran
durante la traduccion, el nombre del archivo de salida, del archivo de
entrada a traducir, y el archivo de palabras ignoradas
*/

void translate(dict_t dict, dict_t temp, dict_t ignore,
                 char *file_intput, char *file_otput, char *file_ignore);