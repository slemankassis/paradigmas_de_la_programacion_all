# Recuperatorios - Consignas Adicionales

## Laboratorio 1

1. Agregar un diccionario personal, el cual contendrá las palabras que el usuario agrega. Es decir, ahora la aplicación debe tener dos diccionarios, uno principal que tiene traducciones por defecto y nunca se modifica (opcionalmente pasado con el parámetro `-d`), y otro personal que se actualiza con las traducciones agregadas por el usuario. Ustedes definen dónde guardar este último. Al momento de traducir, tiene precedencia el diccionario personal, es decir, primero se busca la traducción en el diccionario personal, si esta no existe, se busca en el diccionario principal. 


## Laboratorio 2

En este recuperatorio se evaluará fuertemente la arquitectura de la aplicación y la utilización correcta de clases.

1. Definir una interfaz para los diccionarios (ej: una interfaz llamada IDictionary).

2. Dar dos implementaciones de Diccionarios distintas que implementen la interfaz que introdujeron.

3. Agregar un parámetro  `-m (--implementation)` que reciba `0` o `1` y permita elegir la implementación de diccionario a utilizar. El código deberá ser genérico y poder trabajar con ambas implementación de forma indistinta (ej: "programar contra la interfaz").

## Laboratorio 3

En el recuperatorio se evaluará fuertemente que se haga uso debido de las funciones de librería para listas, como `fold` (`left` y `right`), `map`, `filter`, etc. Si se encuentran haciendo recursion y haciendo pattern matching sobre una lista, en muchos casos pueden utilizar en vez una de estas funciones.

1. Reemplazar recursión y pattern matching por el uso de las funciones de librería para listas.

## Laboratorio 4

1. Implementar la autenticación utilizando un tercer servicio, como ser Facebook, Twitter o Bitbucket.

2. Aplicar protección de ataques CSRF a formularios vulnerables.

## Entrega de los recuperatorios

- **Fecha de entrega:**  Hasta el viernes 17/06 a las 23:59:59.9999

- **Tags Requeridos:** Para poder identificar los diferentes laboratorios que debemos corregir el tag a utilizar será: `Rx` donde `x` es el número del laboratorio. Por ejemplo, el tag para el recuperatorio del lab 2 sería `R2`, para el lab 4, `R4`, etc. 
