open React;
open Setting;
open Together;

let borderColors = enter => enter ? "rgba(255,0,0,0.8)" : "transparent";

[@react.component]
let make = (~icon: string, ~value: option(string)=?) =>
  <GridItem
    style={ReactDOMRe.Style.combine(
      cursorPointer,
      ReactDOMRe.Style.make(~position="relative", ()),
    )}
    enterBorderStyle="solid"
    enterBorderColor="rgba(255,0,0,0.8)"
    xs="no">
    <Card width="112px" height="120px">
      <div
        style={ReactDOMRe.Style.make(
          ~position="absolute",
          ~top="50%",
          ~left="50%",
          ~height="24px",
          ~transform="translate(-50%, -50%)",
          (),
        )}>
        <IconAction animation="leftRight" src=icon />
      </div>
      <div
        style={ReactDOMRe.Style.make(
          ~position="absolute",
          ~bottom="10%",
          ~left="50%",
          ~transform="translate(-50%, -100%)",
          (),
        )}>
        <Typography variant="subtitle2" noWrap=true>
          {value |> stringObjects |> string}
        </Typography>
      </div>
    </Card>
  </GridItem>;