open ReasonReact;
open Setting;

[@react.component]
let make =
    (
      ~startIcon: string,
      ~onChange: option(ReactEvent.Form.t => unit)=?,
      ~onKeyDown: option(ReactEvent.Keyboard.t => unit)=?,
      ~value: option(string)=?,
      ~disabled: option(bool)=?,
      ~showLine: option(bool)=?,
      ~clickEnd: option(ReactEvent.Mouse.t => unit)=?,
      ~endIcon: string,
    ) =>
  <GridItem top="0" bottom="0" left="6" xs="12">
    <GridContainer direction="row" justify="around" alignItem="center">
      <GridItem top="20" right="6" bottom="0" left="0" xs="no">
        <IconAction animation="leftRight" src=startIcon />
      </GridItem>
      <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
        <TextFieldStandard
          top="0"
          bottom="0"
          placeholder="Option"
          value={value |> stringObjects}
          disabled={disabled |> disabledObjects}
          ?onChange
          ?onKeyDown>
          null
        </TextFieldStandard>
      </GridItem>
      {showLine |> disabledObjects
         ? <GridItem top="20" right="0" bottom="0" xs="no">
             <IconButton
               padding="12"
               disabled={disabled |> disabledObjects}
               onClick=?clickEnd>
               <IconAction animation="circle" src=endIcon />
             </IconButton>
           </GridItem>
         : null}
    </GridContainer>
  </GridItem>;
