open Setting;
[%bs.raw {|require('../../scss/Chip/chip.scss')|}];

let components = variant =>
  switch (variant) {
  | "Link"
  | "a" => "a"
  | _ => "div"
  };

let margins = margin =>
  switch (margin) {
  | None => "8px"
  | Some(margin) => margin ++ "px"
  };

let borderWidths = borderWidth =>
  switch (borderWidth) {
  | None => "1px"
  | Some(borderWidth) => borderWidth ++ "px"
  };

let borderStyles = borderStyle =>
  switch (borderStyle) {
  | None => "solid"
  | Some(borderStyle) => borderStyle
  };

let borderColors = borderColor =>
  switch (borderColor) {
  | None => "rgba(0,0,0,0.23)"
  | Some(borderColor) => borderColor
  };

[@react.component]
let make =
    (
      ~variant: option(string)=?,
      ~style: option(ReactDOMRe.style)=?,
      ~top: option(string)=?,
      ~right: option(string)=?,
      ~bottom: option(string)=?,
      ~left: option(string)=?,
      ~borderWidth: option(string)=?,
      ~borderStyle: option(string)=?,
      ~borderColor: option(string)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~children,
    ) =>
  ReactDOMRe.createDOMElementVariadic(
    variant |> stringObjects |> components,
    ~props=
      ReactDOMRe.domProps(
        ~style={
          ReactDOMRe.Style.combine(
            ReactDOMRe.Style.make(
              ~marginTop={
                top |> margins;
              },
              ~marginRight={
                right |> margins;
              },
              ~marginBottom={
                bottom |> margins;
              },
              ~marginLeft={
                left |> margins;
              },
              ~borderWidth={
                borderWidth |> borderWidths;
              },
              ~borderStyle={
                borderStyle |> borderStyles;
              },
              ~borderColor={
                borderColor |> borderColors;
              },
              (),
            ),
            style |> styleObjects,
          );
        },
        ~role="button",
        ~className="j8nrp8lcp juyseni j189749r",
        ~onClick?,
        (),
      ),
    [|children|],
  );