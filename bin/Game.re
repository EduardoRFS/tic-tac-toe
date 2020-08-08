open Error;

let (let.ok) = Result.bind;

let next_player =
  Player.(
    fun
    | Player_1 => Player_2
    | Player_2 => Player_1
  );

let find_winner = ((x, y), board: Board.t) => {
  open Board;
  let get = (x, y) => get((x mod 3, y mod 3), board) |> Result.get_ok;

  let line = (get(x, y), get(x + 1, y), get(x + 2, y));
  let column = (get(x, y), get(x, y + 1), get(x, y + 2));

  // TODO: optimize that to use only new change
  let diagonal_left = (get(0, 0), get(1, 1), get(2, 2));
  let diagonal_right = (get(2, 0), get(1, 1), get(0, 2));

  let check =
    fun
    | (Some(player_a), Some(player_b), Some(player_c)) =>
      player_a == player_b && player_b == player_c ? Some(player_a) : None
    | _ => None;

  [line, column, diagonal_left, diagonal_right] |> List.find_map(check);
};

type turn =
  | Player(Player.t)
  | Done;

type state = {
  board: Board.t,
  turn,
};

type action =
  | Select(Board.position);

let initial = {board: Board.empty, turn: Player(Player_1)};
let is_done = (position, board) =>
  Board.is_full(board) || Option.is_some(find_winner(position, board));

let select = (position, player, board) => {
  let.ok board = Board.place(position, player, board);
  is_done(position, board)
    ? Ok({board, turn: Done})
    : Ok({
        // TODO: validate if is done
        board,
        turn: Player(next_player(player)),
      });
};
let dispatch = (action, {board, turn}) =>
  switch (action, turn) {
  | (_, Done) => Error(Game_already_done)
  | (Select(position), Player(player)) => select(position, player, board)
  };
