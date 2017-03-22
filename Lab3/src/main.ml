open Jugador
open Ronda


let _ =
  let j_totales, mazo = crear_jugadores_y_repartir() in
  nueva_ronda mazo j_totales

