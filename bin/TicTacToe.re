module State = {
  type player =
    | Player_1
    | Player_2;

  module Board = {
    type t = array(option(player));
    let get_index = ((x, y)) => y * 3 + x;
    let get = ((x, y), t) => t[get_index((x, y))];
    let set = ((x, y), player, t) =>
      Array.copy(t)[get_index((x, y))] = Some(player);
  };

  type turn =
    | Player(player)
    | Done;

  type t = (Board.t, turn);
};

module Action = {
  type position = (int, int);
  type t =
    | Select(position);
};

Console.log("tuturu");
