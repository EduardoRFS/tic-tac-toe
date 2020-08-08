open Game;

let actions = [
  Select((0, 0)),
  Select((1, 0)),
  Select((0, 1)),
  Select((1, 1)),
  Select((0, 2)),
];

let state =
  actions
  |> List.fold_left(
       (state, action) =>
         Result.bind(state, state => dispatch(action, state)),
       Ok(initial),
     )
  |> Result.get_ok;

Marshal.to_string(actions, []) |> Console.log;
