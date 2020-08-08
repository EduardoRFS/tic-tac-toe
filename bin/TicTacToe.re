type error =
  | Position_already_selected
  | Game_already_done;

type player =
  | Player_1
  | Player_2;

type position = (int, int);

module Board = {
  type t = array(option(player));
  let get_index = ((x, y)) => y * 3 + x;
  let get = (position, t) => t[get_index(position)];
  let set = (position, player, t) => {
    let new_board = Array.copy(t);
    new_board[get_index(position)] = Some(player);
    new_board;
  };

  /* fail if already was placed */
  let place = (position, player, t) =>
    switch (get(position, t)) {
    | Some(_) => Error(Position_already_selected)
    | None => Ok(set(position, player, t))
    };
};

type turn =
  | Player(player)
  | Done;

type state = (Board.t, turn);

type action =
  | Select(position);

let next_player =
  fun
  | Player_1 => Player_2
  | Player_2 => Player_1;

let someone_won = (board: Board.t) => {
  open Board;
  // TODO: optimize that to use only new change
  let get_line = y => (
    board |> get((0, y)),
    board |> get((1, y)),
    board |> get((2, y)),
  );
  let get_column = x => (
    board |> get((x, 0)),
    board |> get((x, 1)),
    board |> get((x, 2)),
  );
  let get_diagonal_x = () => (
    board |> get((0, 0)),
    board |> get((1, 1)),
    board |> get((2, 2)),
  );
  let get_diagonal_y = () => (
    board |> get((2, 0)),
    board |> get((1, 1)),
    board |> get((0, 2)),
  );

  let check =
    fun
    | (Some(player_a), Some(player_b), Some(player_c)) =>
      player_a == player_b && player_b == player_c ? Some(player_a) : None
    | _ => None;

  [
    check(get_column(0)),
    check(get_column(1)),
    check(get_column(2)),
    check(get_line(0)),
    check(get_line(1)),
    check(get_line(2)),
    check(get_diagonal_x()),
    check(get_diagonal_y()),
  ]
  |> List.find_map(Fun.id);
};
let is_done = board =>
  !Array.exists(Option.is_none, board) || Option.is_some(someone_won(board));

let select = (position, player, board) =>
  Board.place(position, player, board)
  |> Result.map(board =>
       is_done(board)
         ? (board, Done)
         : (
           // TODO: validate if is done
           board,
           Player(next_player(player)),
         )
     );
let run = (action, (board, turn)) =>
  switch (turn) {
  | Done => Error(Game_already_done)
  | Player(player) =>
    switch (action) {
    | Select(position) => select(position, player, board)
    }
  };
Console.log("tuturu");
