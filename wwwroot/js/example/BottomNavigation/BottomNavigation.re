open ReasonReact;
open Setting;

[@react.component]
let make =
    (
      ~actionShow: option(bool)=?,
      ~disabled: option(bool)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~icon: string,
      ~tile: option(string)=?,
    ) =>
  <NavigationAction
    actionShow={actionShow |> disabledObjects}
    disabled={disabled |> disabledObjects}
    ?onClick>
    ...(<IconGeneral src=icon />, tile |> stringObjects |> string)
  </NavigationAction>;