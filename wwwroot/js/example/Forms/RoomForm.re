open ReasonReact;
open Setting;

[@react.component]
let make =
    (
      ~startIcon: string,
      ~roomValue: option(string)=?,
      ~disabled: option(bool)=?,
      ~changeRoom: option(ReactEvent.Form.t => unit)=?,
      ~keyDownRoom: option(ReactEvent.Keyboard.t => unit)=?,
      ~ageValue: option(string)=?,
      ~changeAge: option(ReactEvent.Form.t => unit)=?,
      ~keyDownAge: option(ReactEvent.Keyboard.t => unit)=?,
      ~priceValue: option(string)=?,
      ~changePrice: option(ReactEvent.Form.t => unit)=?,
      ~keyDownPrice: option(ReactEvent.Keyboard.t => unit)=?,
      ~showLine: option(bool)=?,
      ~clickEnd: option(ReactEvent.Mouse.t => unit)=?,
      ~endIcon: string,
    ) =>
  <GridItem top="0" bottom="0" left="6" xs="12">
    <GridContainer direction="row" justify="start" alignItem="center">
      <GridItem top="20" right="6" bottom="0" left="0" xs="no">
        <IconAction animation="leftRight" src=startIcon />
      </GridItem>
      <GridItem
        top="0"
        right="0"
        bottom="0"
        left="0"
        width="calc(100% - 380px)"
        xs="no">
        <TextFieldStandard
          top="0"
          bottom="0"
          placeholder="Option"
          value={roomValue |> stringObjects}
          disabled={disabled |> disabledObjects}
          onChange=?changeRoom
          onKeyDown=?keyDownRoom>
          null
        </TextFieldStandard>
      </GridItem>
      <GridItem top="0" bottom="0" width="124px" xs="no">
        <TextFieldStandard
          top="0"
          bottom="0"
          type_="number"
          placeholder="Age"
          value={ageValue |> stringObjects}
          disabled={disabled |> disabledObjects}
          onChange=?changeAge
          onKeyDown=?keyDownAge>
          null
        </TextFieldStandard>
      </GridItem>
      <GridItem top="0" right="0" bottom="0" width="124px" xs="no">
        <TextFieldStandard
          top="0"
          bottom="0"
          type_="number"
          placeholder="Price"
          value={priceValue |> stringObjects}
          disabled={disabled |> disabledObjects}
          onChange=?changePrice
          onKeyDown=?keyDownPrice>
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
