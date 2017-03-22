open List


type palo = C | O | B | E | ID | SWAP | MAX | MIN | TOP | PAR
type carta = (palo * int)
type mazo = carta list


let carta_inicial = (C, 1)

let mazo_completo = [
                     (C, 1);(C, 2);(C, 3);(C, 4);(C, 5);(C, 6);(C, 7);(C, 8);
                     (C, 9);(C, 10);(C, 11);(C, 12);
                     (O, 1);(O, 2);(O, 3);(O, 4);(O, 5);(O, 6);(O, 7);(O, 8);
                     (O, 9);(O, 10);(O, 11);(O, 12);
                     (B, 1);(B, 2);(B, 3);(B, 4);(B, 5);(B, 6);(B, 7);(B, 8);
                     (B, 9);(B, 10);(B, 11);(B, 12);  
                     (E, 1);(E, 2);(E, 3);(E, 4);(E, 5);(E, 6);(E, 7);(E, 8);
                     (E, 9);(E, 10);(E, 11);(E, 12);
                     (ID, 0);(SWAP, 0);(MAX, 0);(MIN, 0);(TOP, 0);(PAR, 0)
                    ]


let rec shuffle lista =
  let rec extract acc n = function
    [] -> failwith "shuffle"
    | h :: t -> if n = 0 then (h, acc @ t) else extract (h::acc) (n-1) t
  in
  let extract_rand aux_list len =
    Random.self_init();
    extract [] (Random.int len) aux_list
  in
  let rec aux acc aux_list len =
    if len = 0 then acc else
      let picked, rest = extract_rand aux_list len in
      aux (picked :: acc) rest (len-1)
  in
  aux [] lista (List.length lista)


let rec eliminar_elementos n xs = match n, xs with
  _, [] -> failwith "eliminar_elementos"
| 0, xs -> xs
| _, x :: xs -> eliminar_elementos (n-1) xs


let rec eliminar_elemento a xs = match xs with
  [] -> failwith "eliminar_elemento"
| x :: xs -> if x = a then
               xs
             else
               x :: eliminar_elemento a xs


let rec existe_elemento a xs = match xs with
  [] -> false
| x :: xs -> if x = a then
               true
             else
               existe_elemento a xs


let rec primeros_elementos n xs = match n, xs with
  _, [] -> failwith "primeros_elementos"
| 0, xs -> []
| _, x :: xs -> x :: primeros_elementos (n-1) xs



let carta_maxima mazo =
  let rec maximo_palo mazo = match mazo with
    [] -> C
  | (_, 0) :: xs -> maximo_palo xs
  | (p, _) :: xs -> max p (maximo_palo xs)
  in
  let rec maximo_numero palo_maximo mazo = match mazo with
    [] -> 1
  | (p, i) :: xs -> if p = palo_maximo then
                      max i (maximo_numero palo_maximo xs)
                    else
                      maximo_numero palo_maximo xs
  in
  let palo_maximo = maximo_palo mazo in
  palo_maximo, maximo_numero palo_maximo mazo


let carta_minima mazo =
  let rec minimo_palo mazo = match mazo with
    [] -> E
  | (_, 0) :: xs -> minimo_palo xs
  | (p, _) :: xs -> min p (minimo_palo xs)
  in
  let rec minimo_numero palo_minimo mazo = match mazo with
    [] -> 12
  | (p, i) :: xs -> if p = palo_minimo then
                      min i (minimo_numero palo_minimo xs)
                    else
                      minimo_numero palo_minimo xs
  in
  let palo_minimo = minimo_palo mazo in
  palo_minimo, minimo_numero palo_minimo mazo


let rec cartas_pares mazo = match mazo with
  [] -> []
| (_, 0) :: xs -> cartas_pares xs
| (p, i) :: xs -> (
                  match i mod 2 with
                  | 0  -> (p,i) :: (cartas_pares xs)
                  | _ -> cartas_pares xs
                  )


let rec imprimir_cartas mazo = match mazo with
  [] -> Printf.printf "";
| (p, i) :: xs -> (
                  match p with
                    C -> Printf.printf "C%i " i
                  | O -> Printf.printf "O%i " i
                  | B -> Printf.printf "B%i " i
                  | E -> Printf.printf "E%i " i
                  | ID -> Printf.printf "SID "
                  | SWAP -> Printf.printf "SSWAP "
                  | MAX -> Printf.printf "SMAX "
                  | MIN -> Printf.printf "SMIN "
                  | TOP -> Printf.printf "STOP "
                  | PAR -> Printf.printf "SPAR "
                  );
                  imprimir_cartas xs


let carta_valor carta =
  let valor = int_of_string (String.sub carta 1 (String.length carta - 1)) in
  if valor < 1 && valor > 12 then
    raise Not_found
  else
    valor


let leer_carta carta =
  let longitud = String.length carta in
  if longitud < 2 then
    raise Not_found
  else
    match String.get carta 0 with
      'C' -> C, carta_valor carta
    | 'O' -> O, carta_valor carta
    | 'B' -> B, carta_valor carta
    | 'E' -> E, carta_valor carta
    | 'S' -> let carta_esp = String.sub carta 1 (longitud - 1) in
             (
              match carta_esp with
                "ID" -> ID, 0
              | "SWAP" -> SWAP, 0
              | "MAX" -> MAX, 0
              | "MIN" -> MIN, 0
              | "TOP" -> TOP, 0
              | "PAR" -> PAR, 0
              | _ -> raise Not_found
             )
    | _ -> raise Not_found


let es_carta_especial carta = match carta with
  (_, 0) -> true
| _ -> false


let rec todas_cartas_especiales jugador_cartas = match jugador_cartas with
  [] -> true
| (_, 0) :: xs -> true && todas_cartas_especiales xs
| (_, _) :: xs -> false


(* elimino ys de xs: filter (fun x -> not (mem x ys)) xs *)
let carta_especial carta cartas_jugador mazo =
  let cartas_jugador_actualizado = eliminar_elemento carta cartas_jugador in
  match carta with
    (s, 0) -> (
               match s with
                 ID -> cartas_jugador_actualizado, mazo
               | SWAP -> mazo, cartas_jugador_actualizado
               | MAX -> let aux = carta_maxima mazo in
                        cartas_jugador_actualizado @ [aux], eliminar_elemento aux mazo
               | MIN -> let aux = carta_minima cartas_jugador_actualizado in
                        eliminar_elemento aux cartas_jugador_actualizado, mazo @ [aux]
               | TOP -> cartas_jugador_actualizado @ [List.hd mazo], List.tl mazo
               | PAR -> let aux = cartas_pares mazo in
                        cartas_jugador_actualizado @ aux, filter (fun x -> not (mem x aux)) mazo
               | _ -> failwith "carta_especial"
              )
  | (_, _) -> failwith "carta_especial"

