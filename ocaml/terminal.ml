let generation_width = 170
let generation_height = 170
let generation_size = generation_width * generation_height

let (%) a b = ((a mod b) + b) mod b

let calculate_alive_neigbours generation i =
    let rec helper acc dx dy ix iy =
        let x = (ix + dx) % generation_width in
        let y = (iy + dy) % generation_height in
        let i = (x + y * generation_width) % generation_size in
        let new_acc = acc + (Array.get generation i) in
        match dy with
        | 0 -> (match dx with
            | 0 -> helper acc (dx + 1) dy ix iy
            | -1 | 1 -> helper new_acc (dx + 1) dy ix iy
            | 2 -> helper acc 0 (dy + 1) ix iy
            | _ -> 0)
        | -1 | 1 -> (match dx with
            | 0 | -1 | 1 -> helper new_acc (dx + 1) dy ix iy
            | 2 -> helper acc 0 (dy + 1) ix iy
            | _ -> 0)
        | 2 -> (match dx with
            | 0 | -1 | 1 -> helper new_acc (dx + 1) dy ix iy
            | 2 -> new_acc
            | _ -> 0)
        | _ -> 0
    in
    helper 0 (-1) (-1) (i mod generation_width) (i / generation_width);;

let next_state generation i =
    let neighbours = calculate_alive_neigbours generation i in
    match Array.get generation i with
    | 1 -> (match neighbours with
        | 2 | 3 -> 1
        | _ -> 0)
    | 0 -> (match neighbours with
        | 3 -> 1
        | _ -> 0)
    | _ -> 0

let print_cell i = function
    | 0 -> (match i mod generation_width with
        | 0 -> print_endline " "
        | _ -> print_char ' ')
    | 1 -> (match i mod generation_width with
        | 0 -> print_endline "●"
        | _ -> print_string "●")
    | _ -> ()

let rec play generation =
    Array.iteri print_cell generation;
    let next_generation = Array.init generation_size (fun i -> (next_state generation i)) in
    play next_generation;;

let () =
    let generation = Array.init generation_size (fun _ -> Random.int 2) in
    play generation;;
