#Introduccion

*Se implementa el traductor con un tad basado en lista enlazadas. Reciclamos el proyecto 2 de la materia Algortimos y Estructuras de Datos II. Eliminando los campos length de las struct propiamente dichas, poniendo 2 index en lugar de 1 index y 1 data para la palabra en ingles y para la de español.

*Se logra una buena abstraccion y ocultamiento de informacion de los tads. Agregamos luego 3 archivos mas que utilizaban el tad conjunto del diccionario, es decir dict, list, pair y por ultimo index. Estos 3 archivos ya se encargan de la traduccion propiamente dicha, los veamos en detalles "de arriba hacia abajo" para entender cuando se necesita cada una y de sus funciones internas:



#dict.{c,h}

*Se implemento una funcion nueva(dict_data_system) que crea y carga un dicccionario por defecto en caso de que el usuario no ingrese ningun diccionario


#translate.{c,h}

*Este archivo tiene una sola funcion que lleva el mismo nombre pero se decidio escribir una cabecera para dejar mas prolijo el Makefile y por si crece el codigo o modularizarse mas.


##Funcion translate

*Esta funcion toma 6 argumentos: el diccionario principal de traduccion que contiene la forma "palabra-español,palabra-inglés" y asi sucesivamente, un par por linea, este diccionario si no lo ingresa el usuario, se lo crea vacio; un diccionario temporal, cargado en memoria con nuestro sistema de tads y subtads dict, el diccionario temporal; un diccionario de palabras ignoradas que es ingresado por el usuario o se crea caso contrario. Los ultimos 3 argumentos son los paths o nombres del archivo ingresado a traducir, la de volcado del archivo traducido y el de palabras ignoradas.

*Vamos a explicarla por partes. Las partes 2, 3 y 4 van dentro de un ciclo que recorre todo el archivo a traducir, usamos feof.

###Primera parte, inicializacion.
*Se inicializa un contador necesario para algun loop mas adelante, una variable flag que se utilizara para tratar las palabras con mayusculas y se crea lo necesario para abrir con fopen los 3 archivos ingresados a la funcion (son los ultimos 3 argumentos). El archivo a traducir como solo lectura y los otros dos como escritura.

###Segunda parte, caracteristicas de las palabras.
*Se comprueba que sea una caracter alfanumerico con o sin acentos, en caso de no serlo se determina que los caracteres que se venian leyendo anteriormente forma una palabra.

###Tercera parte, busqueda en diccionarios.
*Aca con 4 condicionales secuenciales consultamos si la traduccion esta: en el diccionario ingresado por el usuario, en el diccionario de "traducir como" que es donde el usuario notifica que una palabra que no se encontro se quiere reemplazar con una traduccion "manual" y en el diccionario de palabras ignoradas. 
*Cabe aclarar que cuando se habla de diccionario de palabras ignoradas ya estamos en un nivel de abstraccion, relamente es un archivo con una lista de palabras adentro. 
*Como ultima opcion devuelve en pantalla las 4 opciones que se pidieron en consigna y que marcaron estos diseños de implementacion: Ignorar (i) - Ignorar Todas (h) - Traducir como (t) - Traducir siempre como (s).
*Estas opciones se tratan en la seccion de word_user.
*Se decidio mostrar el mensaje aca y para no sobrecargar la subfuncion llamada y para que quede mas limpia la interfaz, sin embargo la escucha de la opcion se hace en word_user.

###Cuarta parte,
*se "devuelve" la caracteristica a la palabra y se libera la memoria del buffer que se uso en la palabra (1 palabra por loop).

###Quinta parte,
*se vuelca la traduccion al archivo de salida, se cierran los 3 archivos, se libera la memoria del buffer de la palabra a traducir y del buffer de la traduccion.



#try_char.{c,h}

*Contiene 3 funciones. 

##Funcion valid_char

*Verificar que un caracter sea valido, esto se hace por seguridad para que no hayan inyecciones de codigo o stacksoverflows, para ello usamos comparaciones directas con "<=", en minusculas, mayuculas y numeros.

##Funcion change_mayus_minus

*Como indica el nombre, se utiliza para cambiar de mayuscula a minuscula y viceversa. Los detalles de como se trabaja con numeracion de caracteres ASCII estan especificados en los comentarios de su codigo.

##Funcion is_mayus

*Funcion que devuelve true si la letra es mayuscula.



#option_user.{c,h}

*Contiene una funcion principal declarada en el archivo de cabecera. Al igual que translate.h, esta option_user se crea por si crece la implementacion.
*Contiene ademas 2 funciones auxiliares internas. Una para el menu de opciones que se le presenta al usuario, ya sea ignorar, ignorar todas, traducir comoy traducir siempre como. La otra funcion se ocupa de hacer un intercambio cuando el diccionario es "reverso", es decir ing-esp, y se utiliza en las ultimas dos opciones que estan para traducir como, se la utiliza con un if dentro de ellas.


##Funcion word_user

*Veamos la funcion principal. Toma en los argumentos a los 3 diccionarios y el buffer de palabra a traducir. Analicemos que sucede en cada caso elegido por el usuario.

###Ignorar, i.
*Se presentan 2 ideas, eliminar la palabra o pasar la no traducida. Decidimos la segunda copiando los traductores clasicos como Google Translate, ademas que nos parecio mas prolijo.

###Ignorar todas, h.
*Usamos dict_add y le pasamos el diccionario de palabras ignoradas.

###Traducir como, t.
*El usuario elije esa ocpcion y luego teclea la palabra que sera agregada a la variable respectiva de palabra traducida (buff_translated) y luego se pasa ese parametro y el diccionario temporal ya que nos servira para todo el documento.

###Traducir siempre como, s.
*Lo mismo que la anterior en cuanto a leer lo ingresado, cargarlo en memoria y pasarlo como parametro a dict_add y se agrega al diccionario prinpipal, luego se actualiza el archivo al final del programa.



#Main (main.c)

*Explicamos a continuacion la funcion main por partes secuencialmente y nos vamos intruciendo a cada llamado de funcion auxiliar a medida que la necesitemos (explicacion DFS).

*La funcion main toma 2 argumentos, argc que es la cantidad de argumentos que tiene nuestra llamada al programa desde la consola y argv que son los argumentos propiamente dichos. Vamos a verificar que el ingreso del archivo a traducir este si o si y si no sale directamente porque no tendria sentido ejecutar nada del programa.

##Primera parte, inicializacion.
*La estructura llamada "arguments" consta de: args cantidad de argumentos del argumento, es decir el file y debe ser solo 1; input_file, dict_file, dict_ignored_file, output_file que son los argumentos de cada argumento -i, -d, -g y -o respectivamente; y un entero bandera que se usa para ver el sentido de la traduccion.
*Se inicializa dicha estructura con valores nulos y se crean 3 diccionarios, por mas que alguno de los dos ultimos pueda no usarse. Esto es para que sea mas facil de ver y entender el codigo.

##Segunda parte, parseo de argumentos.
*Se analizaron las 2 forman recomendadas por la catedra para la lectura de los argumentos: getopt y argp. Se utiliza la forma argp, nos parecio mas limpia ya que hace los casos en la funcion, para ello se incluye la libreria respectiva y se adecuo a nuestras necesidades para el proyecto.
*Se llama a la funcion argp_parse que devuelve una estructura error_t. Interiormente esta funcion analiza con switch cada caso posible y modifica 1 parte de la estructura arguments.
*Documento de entrada, Direccion de la traduccion: Setea 1 a input_file o reverse respectivamente.
*Diccionario de traduccion, Diccionario de palabras ignoradas, Archivo de salida: Asigna arg a dict_file, dict_ignored_file, output_file respectivamente.

##Tercera parte, carga de diccionario en memoria.
Primero verifica que se haya ingresado el archivo a traducir, es decir que arguments.input_file si o si tenga 1 y sino sale del programa tirando mensaje de error. Luego procede a la creacion de estructuras de diccionario con listas enlazadas usando dict_from_file habiendo sido ingresado en los argumentos o no, es decir que si falta alguno crea el archivo .txt. Por ultimo hay un quinto condicional que se ocupa de cambiar el valor de dict reverse.
Dict reverse es un campo que se decidio colocar como valor booleano en la estructura dict.

##Cuarta parte, 
*llamada a la funcion translate.

##Quinta parte,
*actualiza el el .txt de palabras ignoradas volcando el dict_ignored con la funcion dict_to_file que usa dump.

##Sexta parte,
*se destruyen las 3 estructuras dict usadas. Y se sale llamando a la funcion exit.



#Conclusion
*Este laboratorio nos permitio decidir como encarar un problema en su totalidad con una implementacion, excepto el lenguaje. Cada decision de diseño la tuvimos que tomar nosotros con los recursos que fuimos logrando a lo largo de la carrera en materias troncales como son los algoritmos y estructuras de datos.
*Utilizamos los softwares o scripts cpplint, cppcheck y valgrind para analizar estilo, semantica y uso de memoria respectivamente.




#Compilacion

Abrir terminal (Ctrl + Alt + t)

$ cd <path_of_"Lab1">

$ make
