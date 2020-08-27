open ReasonReact;
open Setting;

[@react.component]
let make =
    (
      ~startIcon: string,
      ~onChange: option(ReactEvent.Form.t => unit)=?,
      ~onKeyDown: option(ReactEvent.Keyboard.t => unit)=?,
      ~enterBorderColor: option(string)=?,
      ~downBorderColor: option(string)=?,
      ~borderColor: option(string)=?,
      ~value: option(string)=?,
      ~disabled: option(bool)=?,
      ~showLine: option(bool)=?,
      ~clickCenter: option(ReactEvent.Mouse.t => unit)=?,
      ~centerIcon: string,
      ~clickEnd: option(ReactEvent.Mouse.t => unit)=?,
      ~endIcon: string,
    ) =>
  <GridItem top="0" bottom="0" left="6" xs="12">
    <GridContainer direction="row" justify="start" alignItem="end">
      <GridItem top="0" right="0" bottom="0" left="0" xs="no">
        <IconButton padding="8">
          <IconAction animation="leftRight" src=startIcon />
        </IconButton>
      </GridItem>
      <GridItem top="0" right="6" bottom="0" left="0" xs="auto">
        <TextFieldStandard
          top="0"
          enterBorderColor={enterBorderColor |> stringObjects}
          downBorderColor={downBorderColor |> stringObjects}
          borderColor={borderColor |> stringObjects}
          placeholder="Option"
          value={value |> stringObjects}
          disabled={disabled |> disabledObjects}
          ?onChange
          ?onKeyDown>
          null
        </TextFieldStandard>
      </GridItem>
      {showLine |> disabledObjects
         ? <>
             <GridItem top="0" right="6" bottom="0" left="0" xs="no">
               <IconButton
                 padding="8"
                 disabled={disabled |> disabledObjects}
                 onClick=?clickCenter>
                 <IconAction animation="leftRight" src=centerIcon />
               </IconButton>
             </GridItem>
             <GridItem top="0" right="0" bottom="0" left="0" xs="no">
               <IconButton
                 padding="8"
                 disabled={disabled |> disabledObjects}
                 onClick=?clickEnd>
                 <IconAction animation="circle" src=endIcon />
               </IconButton>
             </GridItem>
           </>
         : null}
    </GridContainer>
  </GridItem>;
