open Cartas


type jugador
type jugadores = jugador list

(*Acceso a los datos de la estructura*)
val nombre : jugador -> string
val puntos : jugador -> int
val cartas : jugador -> mazo
val carta_jugada : jugador -> carta
val actualizar_jugador : jugador -> string -> int -> mazo -> carta -> jugador
val actualizar_puntaje : string -> jugadores -> jugadores

val crear_jugadores_y_repartir : unit -> (jugadores * mazo)

val imprimir_puntajes_jugadores : jugadores -> unit
val jugadores_con_cartas : jugadores -> jugadores
val jugar_carta : mazo -> mazo -> mazo -> bool -> (mazo * carta * mazo * mazo)
