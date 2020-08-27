open React;
open ReasonReact;
open Setting;
[%bs.raw {|require('../../scss/Chip/chipButton.scss')|}];

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

let components = variant =>
  switch (variant) {
  | "Link"
  | "a" => "a"
  | _ => "div"
  };

let disabledBackgroundColors = disabledBackgroundColor =>
  switch (disabledBackgroundColor) {
  | None => "rgba(102,102,102,0.8)"
  | Some(disabledBackgroundColor) => disabledBackgroundColor
  };

let otherBackgroundColors = otherBackgroundColor =>
  switch (otherBackgroundColor) {
  | None => "rgba(0,0,0,0.4)"
  | Some(otherBackgroundColor) => otherBackgroundColor
  };

let backgroundColors = backgroundColor =>
  switch (backgroundColor) {
  | None => "transparent"
  | Some(backgroundColor) => backgroundColor
  };

let colors = color =>
  switch (color) {
  | None => "rgba(0,0,0,0.26)"
  | Some(color) => color
  };

[@react.component]
let make =
    (
      ~variant: option(string)=?,
      ~href: option(string)=?,
      ~style: option(ReactDOMRe.style)=?,
      ~disabledBackgroundColor: option(string)=?,
      ~enterBackgroundColor: option(string)=?,
      ~downBackgroundColor: option(string)=?,
      ~backgroundColor: option(string)=?,
      ~color: option(string)=?,
      ~disabled: option(bool)=?,
      ~children: tupleChildren,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  ReactDOMRe.createDOMElementVariadic(
    variant |> stringObjects |> components,
    ~props=
      ReactDOMRe.domProps(
        ~role="button",
        ~className="j8nrp8lcp juyseni j189749r",
        ~href={
          href |> stringObjects;
        },
        ~onMouseEnter=_ => MouseEnterLeave(true) |> dispatch,
        ~onMouseLeave=_ => MouseEnterLeave(false) |> dispatch,
        (),
      ),
    [|
      fst(children),
      ReactDOMRe.createDOMElementVariadic(
        "span",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.combine(
                ReactDOMRe.Style.make(
                  ~backgroundColor={
                    switch (
                      disabled |> disabledObjects,
                      state.enter,
                      state.down,
                    ) {
                    | (true, _, _) =>
                      disabledBackgroundColor |> disabledBackgroundColors
                    | (false, true, false) =>
                      enterBackgroundColor |> otherBackgroundColors
                    | (false, true, true) =>
                      downBackgroundColor |> otherBackgroundColors
                    | (_, _, _) => backgroundColor |> backgroundColors
                    };
                  },
                  ~color={
                    color |> colors;
                  },
                  (),
                ),
                style |> styleObjects,
              );
            },
            ~className="j2dfb39 j2dfspan",
            ~disabled={
              disabled |> disabledObjects;
            },
            ~onMouseDown=_ => MouseUpDown(true) |> dispatch,
            ~onMouseUp=_ => MouseUpDown(false) |> dispatch,
            ~onMouseEnter=_ => MouseEnterLeave(true) |> dispatch,
            ~onMouseLeave=_ => MouseEnterLeave(false) |> dispatch,
            (),
          ),
        [|snd(children)|],
      ),
    |],
  );
};