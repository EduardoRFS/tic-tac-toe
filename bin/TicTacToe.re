type error =
  | Position_already_selected;

type player =
  | Player_1
  | Player_2;

type position = (int, int);

module Board = {
  type t = array(option(player));
  let get_index = ((x, y)) => y * 3 + x;
  let get = (position, t) => t[get_index(position)];
  let set = (position, player, t) =>
    Array.copy(t)[get_index(position)] = Some(player);

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

Console.log("tuturu");
