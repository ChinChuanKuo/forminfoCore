open React;
open Setting;

let borderLeft = answer =>
  switch (answer) {
  | true => "3px solid rgba(0,145,0,1)"
  | _ => "3px solid rgba(255,0,0,1)"
  };

[@react.component]
let make =
    (
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~showLine: option(bool)=?,
      ~showAnswer: option(bool)=?,
      ~children,
    ) =>
  showLine |> disabledObjects
    ? ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=
          ReactDOMRe.domProps(
            ~style={
              ReactDOMRe.Style.make(~position="relative", ());
            },
            ~onClick?,
            (),
          ),
        [|
          createElementVariadic(
            Paper.make,
            Paper.makeProps(
              ~style={
                ReactDOMRe.Style.make(
                  ~borderLeft={
                    showAnswer |> disabledObjects |> borderLeft;
                  },
                  (),
                );
              },
              ~children,
              (),
            ),
            [||],
          ),
        |],
      )
    : ReactDOMRe.createDOMElementVariadic(
        "div",
        ~props=ReactDOMRe.domProps(~onClick?, ()),
        [|
          createElementVariadic(
            Card.make,
            Card.makeProps(
              ~children={
                createElementVariadic(
                  CardHeader.make,
                  CardHeader.makeProps(~bottom="24", ~children, ()),
                  [||],
                );
              },
              (),
            ),
            [||],
          ),
        |],
      );
