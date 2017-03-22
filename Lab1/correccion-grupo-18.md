# Laboratorio 1 - Corrección 

### Nota: 6 (73.95%)

### Observaciones Generales: 
Buen trabajo. La presencia de algunos errores de funcionalidad mas la presencia de memory leaks y la falta de atención que le pusieron al code styling no permiten una nota mas alta. 
En el futuro presten atención a todos los detalles que se piden, porque en los detalles esta la diferencia.

Sigan así que seguro van a poder promocionar.

## Comentarios
### Funcionalidad (45%)

- No muestra el mensaje "Traducir XXXXXXXX como: YYYYYYYYY" que se pide en los requerimientos del programa.
- Aparentemente hay un diccionario con traducciones predeterminadas que se agregan a las que se obtiene al traducir un documento.
- No traduce la primer ocurrencia de una palabra si la misma no esta en el diccionario.


### Arquitectura (20%)
- Los TADs están bien diseñados. 
- Mi única observaciones es que estuvieron cerca de hacer "over-engineering", ya que quizás la arquitectura podría haber sido mas sencilla, ya que los requerimientos sobre el problema permitían una solución mas sencilla usando arrays.

### Consignas (20%)
- Se detectaron errores de memoria.

	```
	ERROR SUMMARY: 7 errors from 7 contexts
	```

### Code Styling (15%)
- Las descripciones de las funciones en los .h y .c deben ir arriba de la declaración de la función y se deben incluir las descripciones de los argumentos.
- Falta documentar la función `word_user` en **options_user.h**
- Falta documentar la función `translate` en **translate.h**
- No ejecutaron `cpplint`. Tienen 101 errores detectados por la herramienta