open List


type palo
type carta
type mazo = carta list


val carta_inicial : carta
val mazo_completo : mazo

val shuffle : 'a list -> 'a list
val eliminar_elementos : int -> 'a list -> 'a list
val eliminar_elemento : 'a -> 'a list -> 'a list
val existe_elemento : 'a -> 'a list -> bool
val primeros_elementos : int -> 'a list -> 'a list

val carta_maxima : mazo -> carta
val imprimir_cartas : mazo -> unit
val leer_carta : string -> carta
val es_carta_especial : carta -> bool
val todas_cartas_especiales : mazo -> bool
val carta_especial : carta -> mazo -> mazo -> (mazo * mazo)
