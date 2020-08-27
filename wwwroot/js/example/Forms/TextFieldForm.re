open React;
open Setting;

[@react.component]
let make =
    (
      ~className: option(string)=?,
      ~placeholder: option(string)=?,
      ~value: option(string)=?,
      ~disabled: option(bool)=?,
      ~onChange: option(ReactEvent.Form.t => unit)=?,
      ~onKeyDown: option(ReactEvent.Keyboard.t => unit)=?,
    ) =>
  <GridItem top="0" right="0" left="0" xs="12">
    <div className={className |> stringObjects}>
      <TextFieldStandard
        top="0"
        bottom="0"
        placeholder={placeholder |> stringObjects}
        value={value |> stringObjects}
        disabled={disabled |> disabledObjects}
        ?onChange
        ?onKeyDown>
        null
      </TextFieldStandard>
    </div>
  </GridItem>;
