open React;
open Document;

type outitem = {
  disablePadding: bool,
  icon: string,
  value: string,
};

type state = {
  outValue: string,
  showOut: bool,
  outitems: array(outitem),
  showMore: bool,
};

type action =
  | ShowOut
  | ClickItemOutValue(string)
  | ShowMore;

let reducer = (state, action) =>
  switch (action) {
  | ShowOut => {...state, showOut: !state.showOut}
  | ClickItemOutValue(value) => {...state, outValue: value, showOut: false}
  | ShowMore => {...state, showMore: !state.showMore}
  };

let initialState = {
  outValue: "Sans Serif",
  showOut: false,
  outitems: [|
    {disablePadding: false, icon: "", value: {js|微軟正黑體|js}},
    {disablePadding: false, icon: "", value: {js|新細明體|js}},
    {disablePadding: false, icon: "", value: {js|細明體|js}},
    {disablePadding: false, icon: "", value: "Sans Serif"},
    {disablePadding: false, icon: "", value: "Serif"},
    {disablePadding: false, icon: "", value: {js|等寬字型|js}},
    {disablePadding: false, icon: "", value: {js|寬|js}},
    {disablePadding: false, icon: "", value: {js|窄|js}},
    {disablePadding: false, icon: "", value: "Comic Sans MS"},
    {disablePadding: false, icon: "", value: "Garamond"},
    {disablePadding: false, icon: "", value: "Georgia"},
    {disablePadding: false, icon: "", value: "Tahoma"},
    {disablePadding: false, icon: "", value: "Trebuchet MS"},
    {disablePadding: false, icon: "", value: "Verdana"},
  |],
  showMore: false,
};

[@react.component]
let make = (~disabled: bool) => {
  let (state, dispatch) = useReducer(reducer, initialState);

  let clickOutShow = useCallback(_ => ShowOut |> dispatch);
  let clickItemOutValue =
    useCallback(value => {
      value |> Js.log;
      ClickItemOutValue(value) |> dispatch;
      ExecCommands.make("fontName", false, value);
    });
  let clickFormatSize =
    useCallback(_ => ExecCommands.make("fontSize", false, "30px"));
  let clickFormatBold =
    useCallback(_ => ExecCommands.make("bold", false, ""));
  let clickFormatItalic =
    useCallback(_ => ExecCommands.make("italic", false, ""));
  let clickFormatUnderlined =
    useCallback(_ => ExecCommands.make("underline", false, ""));
  let clickStrikethrough =
    useCallback(_ => ExecCommands.make("strikethrough", false, ""));
  let clickFormatAlignLeft =
    useCallback(_ => ExecCommands.make("justifyLeft", false, ""));
  let clickFormatAlignCenter =
    useCallback(_ => ExecCommands.make("justifyCenter", false, ""));
  let clickFormatAlignRight =
    useCallback(_ => ExecCommands.make("justifyRight", false, ""));
  let clickFormatListNumbered =
    useCallback(_ => ExecCommands.make("insertorderedlist", false, ""));
  let clickMoreShow = useCallback(_ => ShowMore |> dispatch);
  let clickFormatClear =
    useCallback(_ => ExecCommands.make("removeFormat", false, ""));

  <AppBar
    backgroundColor="rgba(255,255,255,1)" position="relative" minHeight="40">
    <GridContainer direction="rowReverse" justify="end" alignItem="stretch">
      <GridItem top="0" right="0" bottom="0" left="0" xs="no">
        <IconButton padding="6" onClick=clickMoreShow>
          <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
            {"MoreSetting" |> string}
          </Tooltip>
          <IconAction animation="leftRight" src=Icons.arrowDownBlack />
        </IconButton>
      </GridItem>
      <GridItem
        style={ReactDOMRe.Style.make(
          ~height="25px",
          ~marginTop="6px",
          ~marginRight="3px",
          ~borderRight="1px solid rgba(0,0,0,0.08)",
          (),
        )}
        top="0"
        right="0"
        bottom="0"
        left="3"
        xs="no">
        null
      </GridItem>
      <GridItem top="0" right="0" bottom="0" left="0" xs="no">
        <IconButton padding="6" onClick=clickFormatListNumbered>
          <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
            {"ListNumber" |> string}
          </Tooltip>
          <IconAction
            animation="leftRight"
            src=Icons.formatListNumberedBlack
          />
        </IconButton>
      </GridItem>
      <GridItem top="0" right="0" bottom="0" left="0" xs="no">
        <IconButton padding="6" onClick=clickFormatAlignRight>
          <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
            {"AlignRight" |> string}
          </Tooltip>
          <IconAction animation="leftRight" src=Icons.formatAlignRightBlack />
        </IconButton>
      </GridItem>
      <GridItem top="0" right="0" bottom="0" left="0" xs="no">
        <IconButton padding="6" onClick=clickFormatAlignCenter>
          <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
            {"AlignCenter" |> string}
          </Tooltip>
          <IconAction animation="leftRight" src=Icons.formatAlignCenterBlack />
        </IconButton>
      </GridItem>
      <GridItem top="0" right="0" bottom="0" left="0" xs="no">
        <IconButton padding="6" onClick=clickFormatAlignLeft>
          <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
            {"AlignLeft" |> string}
          </Tooltip>
          <IconAction animation="leftRight" src=Icons.formatAlignLeftBlack />
        </IconButton>
      </GridItem>
      <GridItem
        style={ReactDOMRe.Style.make(
          ~height="25px",
          ~marginTop="6px",
          ~marginRight="3px",
          ~borderRight="1px solid rgba(0,0,0,0.08)",
          (),
        )}
        top="0"
        right="0"
        bottom="0"
        left="3"
        xs="no">
        null
      </GridItem>
      <GridItem top="0" right="0" bottom="0" left="0" xs="no">
        //background color and font color

          <IconButton padding="6" onClick=clickStrikethrough>
            <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
              {"Color" |> string}
            </Tooltip>
            <IconAction animation="leftRight" src=Icons.textFormatBlack />
          </IconButton>
        </GridItem>
      <GridItem top="0" right="0" bottom="0" left="0" xs="no">
        //font underline

          <IconButton padding="6" onClick=clickFormatUnderlined>
            <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
              {"UnderLine" |> string}
            </Tooltip>
            <IconAction
              animation="leftRight"
              src=Icons.formatUnderlinedBlack
            />
          </IconButton>
        </GridItem>
      <GridItem top="0" right="0" bottom="0" left="0" xs="no">
        //font italic

          <IconButton padding="6" onClick=clickFormatItalic>
            <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
              {"Italic" |> string}
            </Tooltip>
            <IconAction animation="leftRight" src=Icons.formatItalicBlack />
          </IconButton>
        </GridItem>
      <GridItem top="0" right="0" bottom="0" left="0" xs="no">
        //font bold

          <IconButton padding="6" onClick=clickFormatBold>
            <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
              {"Bold" |> string}
            </Tooltip>
            <IconAction animation="leftRight" src=Icons.formatBoldBlack />
          </IconButton>
        </GridItem>
      <GridItem
        style={ReactDOMRe.Style.make(
          ~height="25px",
          ~marginTop="6px",
          ~marginRight="3px",
          ~borderRight="1px solid rgba(0,0,0,0.08)",
          (),
        )}
        top="0"
        right="0"
        bottom="0"
        left="3"
        xs="no">
        null
      </GridItem>
      <GridItem top="0" right="0" bottom="0" left="6" xs="no">
        //font size

          <IconButton padding="6" onClick=clickFormatSize>
            <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
              {"Size" |> string}
            </Tooltip>
            <IconAction animation="leftRight" src=Icons.formatSizeBlack />
          </IconButton>
        </GridItem>
      <GridItem top="0" right="0" bottom="0" left="6" xs="auto">
        <SelectStandard
          top="0"
          right="0"
          bottom="0"
          left="0"
          borderTop="10"
          borderBottom="4"
          enterBorderColor="rgba(255,0,0,0.8)"
          downBorderColor="rgba(255,0,0,0.6)"
          borderColor="rgba(0,0,0,0.2)"
          value={state.outValue}
          disabled
          onClick=clickOutShow>
          ...(
               state.showOut
                 ? <SelectMenu
                     top="50%"
                     transform="translate(0, -50%)"
                     width="238"
                     maxHeight="280"
                     minHeight="0">
                     {state.outitems
                      |> Array.map(outitem =>
                           <MenuIcon
                             disablePadding={outitem.disablePadding}
                             onClick={_ => outitem.value |> clickItemOutValue}>
                             ...(
                                  <IconGeneral src={outitem.icon} />,
                                  outitem.value |> string,
                                )
                           </MenuIcon>
                         )
                      |> array}
                   </SelectMenu>
                 : null,
               <IconGeneral
                 animation={state.showOut |> IconAnimation.topDownRorate}
                 src=Icons.arrowDownBlack
               />,
             )
        </SelectStandard>
        <BackgroundBoard
          showBackground={state.showOut}
          backgroundColor="transparent"
          onClick=clickOutShow
        />
      </GridItem>
    </GridContainer>
  </AppBar>;
};