module State = {
  type player =
    | Player_1
    | Player_2;

  type board = array(option(player));

  type turn =
    | Player(player)
    | Done;

  type t = (board, turn);
};

module Action = {
  type position = (int, int);
  type t =
    | Select(position);
};

Console.log("tuturu");
