#Introducción

En este laboratorio se presento la oportunidad de reutilizar nuestro codigo en C adecuandolo a Java. Al pasar el programa a un lenguaje de otro paradigma (a grandes razgos, imperativo a POO), tuvimos que decidir entre usar las clases "estandar" ya existentes que la gran comunidad de Java nos brindaba, o crear nuevas que se adecuen a resolver nuestro proyecto sin crear metodos de mas, o bien ambas. Decicimos la segunda como la opcion que predomina, simplemente por comodidad. Para el parseo de argumentos del main importamos la clase Apache Commons CLI ya que es muy dificil de programar y ya que en C tambien habiamos importado una lib (argp.h).

Se implementa el traductor con una estructura parecida al proyecto uno, pero aprovechando algunas cosas que facilita Java como el uso de ArrayList, el manejo de String, pero sin abusar demasiado de todo esto para no ignorar los conceptos ya adquiridos

Se implementa (o intenta) el uso de polimorfismos para poner en practica una de las características principales del lenguaje y de la programación orientada a objetos. Se tuvo en cuenta las limitaciones que tiene este por el hecho de que las funciones no hacían referencia al mismo tipo de dato de forma "exacta".

#Archivos src (.java)

##Dict

Es una clase abstracta para nombrar las funciones de diccionario necesarias.


##DictTranslate y DictIgnore

Ambas clases heredan de Dict.java los nombres de los metodos y funciones a implementar cada una respectivamente.


#Translate

Al igual que el proyecto uno, este archivo tiene una sola funcion que lleva el mismo nombre.


##Funcion translate

Esta funcion toma 6 argumentos: el diccionario principal(que es cargado de un file), un diccionario temporal(que es creado durante la traducción), una lista de palabras ignoradas(que es cargado de un file) y una lista de palabras ignoradas temporal (que es creada durante la traduccion).

Igual que en el proyecto anterior decidimos cargar el archivo carácter por carácter para tener mayor control sobre las palabras y los caracteres a ignorar para la traducción(sean signos, puntos, comas, espacios, etc) implementando un while que carga los caracteres que va leyendo hasta encontrar un carácter no alfanumérico, una vez tiene la palabra ya creada (por haber leído el archivo) ingresa en una serie de if, que se explican a continuación.

###Búsqueda en diccionarios.
Aca con 3 condicionales secuenciales consultamos si la traducción esta: en el diccionario ingresado por el usuario, en el diccionario de "traducir como" que es donde el usuario notifica que una palabra que no se encontró se quiere reemplazar con una traducción "manual" y el ultimo condicional es verificar que la palabra se encuentre en la lista de palabras ignoradas o la lista que también se puede crear durante la traducción de forma "manual".

Como ultima opción devuelve en pantalla las 4 opciones que se pidieron en consigna y que marcaron estos diseños de implementación: Ignorar (i) - Ignorar Todas (h) - Traducir como (t) - Traducir siempre como (s).
Duchas opciones se tratan en la sección de word_user.

###Luego...
Se "devuelve" la característica a la palabra y se "limpia"(pone a NULL) los String usados para repetir la operación de buscar y traducir una nueva palabra
Finalmente se vuelca la traducción al archivo de salida, se cierran los 2 archivos (el input y output).


##TryChar

Contiene 3 funciones, idem al proyecto uno.

##Función valid_char

Verifica que un carácter sea valido, esto se hace por seguridad para que no hayan inyecciones de código o stacksoverflows, para ello usamos comparaciones directas con "<=", en minúsculas, mayúsculas y números.

##Función change_mayus_minus

Como indica el nombre, se utiliza para cambiar de mayúscula a minúscula y viceversa. Los detalles de como se trabaja con numeración de caracteres ASCII están especificados en los comentarios de su código.

##Función is_mayus

Funcion que devuelve true si la letra es mayuscula.


##OptionUser

Contiene ademas 2 funciones auxiliares internas. Una para el menu de opciones que se le presenta al usuario, ya sea ignorar, ignorar todas, traducir como y traducir siempre como. La otra funcion se ocupa de hacer un intercambio cuando el diccionario es "reverso", es decir ing-esp, y se utiliza en las ultimas dos opciones que están para traducir como, se la utiliza con un if dentro de ellas.
Cabe destacar que la función "SwapString" no resulto tan sencilla como en C dado que Java no tiene manejo de punteros y se usan fuciones especiales para acceder a los valores de punteros he intercambiar las referencias de las variables, de esta forma podemos "devolver" los dos String con el intercambio echo sin necesidad de usar un return con un objeto o similar


##Funcion word_user

Veamos la funcion principal. Toma en los argumentos a los 3 diccionarios y el buffer de palabra a traducir. Analicemos que sucede en cada caso elegido por el usuario.

###Ignorar, i.
Se presentan 2 ideas, eliminar la palabra o pasar la no traducida. Decidimos la segunda copiando los traductores clásicos como Google Translate, además que nos pareció mas prolijo. Pero a diferencia del proyecto uno, ahora el Ignorar es ignorar todas las palabras que se encuentren sin guardarlas en la lista de palabras ignoradas que luego serán guardadas en un file

###Ignorar todas, h.
Usamos dict_add y le pasamos la lista de palabras ignoradas, que luego al finalizar el programa creara un file.txt con la lista de estas palabras

###Traducir como, t.
El usuario elije esa opción y luego ingresa la palabra que sera agregada a la variable respectiva de palabra traducida (buff_translated) y luego se pasa ese parámetro y el diccionario temporal ya que nos servirá para todo el documento.

###Traducir siempre como, s.
Lo mismo que la anterior en cuanto a leer lo ingresado, cargarlo en memoria y pasarlo como parámetro a dict_add y se agrega al diccionario principal, luego se actualiza el archivo al final del programa.



##MainTranslate

La función MainTranslate toma un argumento, que es un arreglos de String que es cargado por los parámetros que le pasamos cuando llamamos el programa por consola. Vamos a verificar que el ingreso del archivo a traducir este si o si y si no sale directamente porque no tendría sentido ejecutar nada del programa.
*Para el parseo de argumentos estaba la posibilidad de hacer de forma "manual" con un codigo simple en el main que constaría de un while, switch, if y no mas(algo facil de hacer) y la otra posibilidad era descargar alguna Lib que nos permitiera implementar las funciones correspondientes para el parseo de argumentos.
*Nos decidimos por la segunda opcion y usamos la librería apache commons-cli-1.2.3.1 (https://commons.apache.org/) que se debe descargar he incluir en el proyecto Java
 
##Primera parte, inicialización.
De forma simple lo que hicimos con esto fue definir nuestros argumentos a usar, la verificación de que estos estén presente y la obtención del valor que trae cada uno respectivamente

##Segunda parte, carga de diccionario en memoria.
Primero verifica que se haya ingresado el archivo a traducir, es decir que arguments.input_file si o si tenga 1 y sino sale del programa tirando mensaje de error. Luego procede a la creacion de estructuras de diccionario con listas enlazadas usando dict_from_file habiendo sido ingresado en los argumentos o no, es decir que si falta alguno crea el archivo .txt. Por ultimo hay un quinto condicional que se ocupa de cambiar el valor de dict reverse.
Dict reverse es un campo que se decidió colocar como valor booleano en la estructura dict.

##Cuarta parte, 
*llamada a la función translate.

##Quinta parte,
*actualiza el el .txt de palabras ignoradas volcando el dict_ignored con la funcion dict_to_file que usa dump.



#Conclusión

*El uso de Java tan de golpe no represento mucha dificultad gracias a la cantidad de información que se encuentra en internet y por el hecho de que es muy similar a C y simplifica muchas cosas como manejo de String y estructura de datos (que ya trae para implementar). Lo que fue nuevo realmente fue el uso de excepciones para la lectura de archivos y lectura de argumentos, que a lo que entendimos es para cuando estos están vacíos o no existen entonces levanta esa excepción, en algunos casos terminando el programa en otros mostrando un mensaje de error únicamente y prosigue el programa
*Otra cosa a destacar que a la hora de ejecutar el .jar debe haber una "disposición" de archivos ya echa en los directorios, en nuestro caso el Jar generado debe estar junto a un directorio lib/ y este debe contener el commons-cli-1.2.3.1.jar esto es por como esta definido el path en el archivo MANIFEST.MF de tal librería para el Jar, en caso de no estar haci no sera posible la ejecución del .jar.



#IDE
Probamos primero con Netbeans y luego parcialemente en Eclipse mas que nada para probar diferencias. Sin embargo mayormente usamos SublimeText, por ende hicimos el MANIFEST.MF manualmente y analizamos en parte la semantica que pudimos buscando errores.



#Estilo de codigo

En principio nos guiamos con estas reglas goo.gl/vucJBJ y despues se paso el checkstyle recomendado por la catedra.



#Compilacion

####Descargar de goo.gl/eTkrIC el binario commons-cli-1.3.1-bin.zip
####Descomprimirlo y copiar commons-cli-1.3.1.jar dentro de la carpeta del proyecto lab2/lib
####Abrir un perfil en Terminal (Ctrl + Alt + T)
####$ *cd <path_del_lab2>*
####$ *make*
