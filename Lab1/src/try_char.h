#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// Corrobora que el caracter a cargar en el buffer sea un alfanumerico.
bool valid_char(char ch);

// El caracter en caso de ser mayuscula cambia a su
// minuscula correspondiente y viceversa.
char change_mayus_minus(char ch);

// Comprueba que un caracter este en mayuscula.
bool is_mayus(char ch);