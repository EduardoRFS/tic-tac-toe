type turn =
  | Player(Player.t)
  | Done;

type state = {
  board: Board.t,
  turn,
};
type action =
  | Select(Board.position);

let initial: state;
let dispatch: (action, state) => result(state, Error.t);
