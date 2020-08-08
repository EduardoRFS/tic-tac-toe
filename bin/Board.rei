[@deriving yojson]
type position = (int, int);
[@deriving yojson]
type t;

let empty: t;
let get: (position, t) => result(option(Player.t), Error.t);
let place: (position, Player.t, t) => result(t, Error.t);
let is_full: t => bool;
