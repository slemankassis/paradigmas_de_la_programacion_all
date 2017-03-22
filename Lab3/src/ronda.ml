open Cartas
open Jugador


exception Mazo_vacio


let rec resolver_ronda carta j_ronda j_todos = match j_ronda with
  [] -> failwith "resolver_ronda"
| x :: xs -> if carta = carta_jugada x then
               (Printf.printf "\nEl jugador %s gano la ronda.\n" (nombre x);
               actualizar_puntaje (nombre x) j_todos)
             else
               resolver_ronda carta xs j_todos


let rec ronda mazo j_turno j_ronda j_todos cartas_ronda = match j_turno with
  [] -> resolver_ronda (carta_maxima cartas_ronda) j_ronda j_todos, mazo
| x :: xs -> Printf.printf "\nMazo: %i cartas." (List.length mazo);
             Printf.printf "\nMazo:  ";
             imprimir_cartas mazo; 
             Printf.printf "\nRonda:  ";
             imprimir_cartas cartas_ronda;
             Printf.printf "\n%s(%i): " (nombre x) (puntos x);
             imprimir_cartas (cartas x);
             Printf.printf "\nQue carta va a jugar %s?  " (nombre x);
             try
               let jugador_cartas_act, carta_leida, cartas_ronda_act, mazo_act =
                 jugar_carta (cartas x) cartas_ronda mazo false
               in
               let jugador_act =
                 actualizar_jugador
                   x
                   (nombre x)
                   (puntos x)
                   (jugador_cartas_act @ [List.hd mazo_act])
                   carta_leida
               in
               let j_ronda_act = (eliminar_elemento x j_ronda) @ [jugador_act] in
               let j_todos_act = (eliminar_elemento x j_todos) @ [jugador_act] in
               ronda (List.tl mazo_act) xs j_ronda_act j_todos_act cartas_ronda_act
             with Mazo_vacio -> Printf.printf
                                  "No se puede usar esa carta especial porque quedan %i cartas en el mazo general, juga otra."
                                  (List.length mazo);
                                ronda mazo (x :: xs) j_ronda j_todos cartas_ronda


let rec nueva_ronda mazo j_todos =
  let jugadores_con_cartas = jugadores_con_cartas j_todos in
  if List.length mazo <> 0 then
    (
     match List.length jugadores_con_cartas with
       0 | 1 -> imprimir_puntajes_jugadores j_todos
     | _ -> let j_todos_act, mazo_act =
              ronda mazo jugadores_con_cartas jugadores_con_cartas j_todos []
            in
            nueva_ronda mazo_act j_todos_act
    )
  else
    (
     Printf.printf "\nEl mazo general tiene %i cartas.\n" (List.length mazo);
     imprimir_puntajes_jugadores j_todos
    )

