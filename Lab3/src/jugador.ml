open Cartas


type jugador =
  {
   nombre: string;
   puntos: int;
   cartas: mazo;
   carta_jugada: carta
  }

type jugadores = jugador list


let nombre jugador = jugador.nombre


let puntos jugador = jugador.puntos


let cartas jugador = jugador.cartas


let carta_jugada jugador = jugador.carta_jugada


let actualizar_jugador jugador nombre puntos cartas carta_jugada =
  {
   nombre = nombre;
   puntos = puntos;
   cartas = cartas;
   carta_jugada = carta_jugada
  }


let rec actualizar_puntaje nombre jugadores = match jugadores with
  [] -> failwith "actualizar_puntaje"
| x :: xs -> if x.nombre = nombre then
               {x with puntos = x.puntos + 1} :: xs
             else
               x :: actualizar_puntaje nombre xs


let lista_nombres _ =
  let rec aux n nombres =
    print_string "Ingrese el nombre del jugador o EXIT para comenzar el juego: ";
    let nombre = read_line() in
    match nombre with
      "EXIT" -> (
                 match n with
                   1 | 2 -> print_string "Minimo 2 jugadores, ingresa mas nombres:\n";
                            aux n nombres
                 | _ -> nombres
                )
    | "" | " " -> print_string "No es nombre valido, intenta de nuevo.\n";
                  aux n nombres
    | _ -> (
            let nombres_actualizado = nombre :: nombres in
            match n with
             5 -> print_string "Maximo 5 jugadores, comienza el juego.\n";
                   nombres_actualizado
            | _ -> aux (n + 1) nombres_actualizado)
  in
  aux 1 []


let crear_jugadores_y_repartir _ =
  let rec aux nombres jugadores mazo = match nombres with
    [] -> jugadores, mazo
  | x :: xs -> let jugador = {
                              nombre = x;
                              puntos = 0;
                              cartas = primeros_elementos 7 mazo;
                              carta_jugada = carta_inicial
                             } in
               let mazo = eliminar_elementos 7 mazo in
               aux xs (jugador :: jugadores) mazo
  in
  aux (lista_nombres()) [] (shuffle mazo_completo)


let rec dar_jugador_puntaje n puntaje jugadores = match jugadores with
  [] -> failwith "dar_jugador_puntaje"
| x :: xs -> if x.puntos = puntaje then
               Printf.printf "%i   %s  %i\n" n x.nombre puntaje
             else
               dar_jugador_puntaje (n + 1) puntaje xs


let imprimir_puntajes_jugadores jugadores =
  print_string "\nGAME OVER. Posiciones:\n";
  let rec aux puntajes_ordenados jugadores = match puntajes_ordenados with
    [] -> exit 0
  | x :: xs -> dar_jugador_puntaje 1 x jugadores;
               aux xs jugadores
  in
  let rec lista_puntajes jugadores = match jugadores with
    [] -> []
  | x :: xs -> x.puntos :: lista_puntajes xs
  in
  aux (List.rev (List.sort compare (lista_puntajes jugadores))) jugadores


let rec jugadores_con_cartas jugadores = match jugadores with
  [] -> []
| x :: xs -> if List.length x.cartas = 0 then
               (
                Printf.printf "El jugador %s ya no tiene cartas.\n" x.nombre;
               jugadores_con_cartas xs
               )
             else
               x :: jugadores_con_cartas xs


let rec jugar_carta cartas cartas_ronda mazo segunda =
  let carta = read_line() in
  flush stdout;
  try
    let carta = leer_carta carta in
    if existe_elemento carta cartas then
      match es_carta_especial carta with
        true -> if segunda && not (todas_cartas_especiales cartas) then
                   raise Not_found
                 else
                   (
                   Printf.printf
                     "La carta especial dio efecto, ahora juga una carta comun para la ronda.\n";
                   let cartas_act, mazo_act = carta_especial carta cartas mazo in
                   imprimir_cartas cartas_act;
                   Printf.printf "\nQue carta va a jugar?  ";
                   jugar_carta cartas_act cartas_ronda mazo_act true
                   )
      | _ -> eliminar_elemento carta cartas, carta, cartas_ronda @ [carta], mazo
    else
      raise Not_found
  with Not_found -> print_string "La carta no es valida, intenta de nuevo.\n";
                    jugar_carta cartas cartas_ronda mazo segunda

