open Cartas
open Jugador


val resolver_ronda : carta -> jugadores -> jugadores -> jugadores
val ronda : mazo -> jugadores -> jugadores -> jugadores -> mazo -> (jugadores * mazo)
val nueva_ronda : mazo -> jugadores -> unit
