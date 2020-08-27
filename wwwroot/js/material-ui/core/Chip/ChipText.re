open React;
open ReasonReact;
open Setting;
[%bs.raw {|require('../../scss/Chip/chipText.scss')|}];

type tupleChildren = (reactElement, reactElement);

type state = {
  enter: bool,
  down: bool,
};

type action =
  | MouseEnterLeave(bool)
  | MouseUpDown(bool);

let reducer = (state, action) =>
  switch (action) {
  | MouseEnterLeave(enter) => {enter, down: enter ? state.down : false}
  | MouseUpDown(down) => {...state, down}
  };

let initialState = {enter: false, down: false};

let otherBackgroundColors = otherBackgroundColor =>
  switch (otherBackgroundColor) {
  | None => "rgba(0,0,0,0.08)"
  | Some(otherBackgroundColor) => otherBackgroundColor
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "transparent"
  | Some(backgroundColor) => backgroundColor
  };

let colors = color =>
  switch (color) {
  | None => "rgba(0,0,0,0.87)"
  | Some(color) => color
  };

[@react.component]
let make =
    (
      ~enterBackgroundColor: option(string)=?,
      ~downBackgroundColor: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~style: option(ReactDOMRe.style)=?,
      ~color: option(string)=?,
      ~children: tupleChildren,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  ReactDOMRe.createDOMElementVariadic(
    "div",
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.make(
            ~backgroundColor={
              switch (state.enter, state.down) {
              | (true, false) => enterBackgroundColor |> otherBackgroundColors
              | (true, true) => downBackgroundColor |> otherBackgroundColors
              | (_, _) => backgroundColor |> backgroundColors
              };
            },
            (),
          );
        },
        ~className="j8nrp8lcts j1s4s3te juysenit",
        ~onMouseDown=_ => MouseUpDown(true) |> dispatch,
        ~onMouseUp=_ => MouseUpDown(false) |> dispatch,
        ~onMouseEnter=_ => MouseEnterLeave(true) |> dispatch,
        ~onMouseLeave=_ => MouseEnterLeave(false) |> dispatch,
        (),
      ),
    [|
      ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=ReactDOMRe.domProps(~className="j4f2n9ip ja16k5a j8idkay", ()),
        [|fst(children)|],
      ),
      ReactDOMRe.createDOMElementVariadic(
        "span",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.combine(
                ReactDOMRe.Style.make(
                  ~color={
                    color |> colors;
                  },
                  (),
                ),
                style |> styleObjects,
              );
            },
            ~className="j1ffzryl",
            (),
          ),
        [|snd(children)|],
      ),
    |],
  );
};