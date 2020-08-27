open ReasonReact;
open Setting;

[@react.component]
let make =
    (
      ~disabled: option(bool)=?,
      ~clickStart: option(ReactEvent.Mouse.t => unit)=?,
      ~startIcon: string,
      ~borderColor: option(string)=?,
      ~value: option(string)=?,
    ) =>
  <GridItem top="6" right="0" left="0" xs="12">
    <GridContainer direction="row" justify="around" alignItem="center">
      <GridItem right="0" bottom="0" left="0" xs="no">
        <IconButton
          padding="12"
          disabled={disabled |> disabledObjects}
          onClick=?clickStart>
          <IconAction animation="leftRight" src=startIcon />
        </IconButton>
      </GridItem>
      <GridItem top="6" right="0" bottom="0" left="0" xs="auto">
        <div
          style={ReactDOMRe.Style.make(
            ~borderBottomWidth="2px",
            ~borderBottomStyle="solid",
            ~borderBottomColor={borderColor |> stringObjects},
            (),
          )}>
          <Typography variant="subtitle1">
            {value |> stringObjects |> string}
          </Typography>
        </div>
      </GridItem>
    </GridContainer>
  </GridItem>;