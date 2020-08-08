open Error;

[@deriving yojson]
type position = (int, int);
[@deriving yojson]
type t = array(option(Player.t));

let (let.ok) = Result.bind;

let empty = Array.make(9, None);

let is_valid_position = ((x, y)) => x >= 0 && x <= 2 && y >= 0 && y <= 2;
let get_index = ((x, y)) =>
  is_valid_position((x, y)) ? Ok(y * 3 + x) : Error(Position_invalid);
let get = (position, t) => {
  let.ok index = get_index(position);
  Ok(t[index]);
};
let set = (position, player, t) => {
  let.ok index = get_index(position);

  let new_board = Array.copy(t);
  new_board[index] = Some(player);
  Ok(new_board);
};

/* fail if already was placed */
let place = (position, player, t) => {
  let.ok element = get(position, t);
  switch (element) {
  | Some(_) => Error(Already_placed)
  | None => set(position, player, t)
  };
};
