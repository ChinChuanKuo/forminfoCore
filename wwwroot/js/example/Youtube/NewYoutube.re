open React;
open Setting;
open OutSide;
open Together;
open ReactIntl;
open Icons;
[%bs.raw {|require('../../../scss/example/Youtube/newYoutube.scss')|}];

type state = {
  formLoad: bool,
  formWidth: int,
  formHeight: int,
  showOpen: bool,
};

type action =
  | SettingFormLoad
  | SettingFormWidth(int, int)
  | ShowOpen;

let reducer = (state, action) =>
  switch (action) {
  | SettingFormLoad => {...state, formLoad: !state.formLoad}
  | SettingFormWidth(width, height) => {
      ...state,
      formWidth: width,
      formHeight: height,
    }
  | ShowOpen => {...state, showOpen: !state.showOpen}
  };

let initialState = {
  formLoad: false,
  formWidth: 0,
  formHeight: 0,
  showOpen: false,
};

let widths = width =>
  switch (width) {
  | None => "80%"
  | Some(width) => width ++ "%"
  };

let bottoms = bottom =>
  switch (bottom) {
  | None => "0px"
  | Some(bottom) => bottom ++ "px"
  };

[@react.component]
let make =
    (
      ~showProgress: option(bool)=?,
      ~error: option(bool)=?,
      ~width: option(string)=?,
      ~bottom: option(string)=?,
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  useEffect(() =>
    if (state.formLoad) {
      Some(() => "action" |> Js.log);
    } else {
      let testId = SettingFormLoad |> dispatch;
      let formId =
        SettingFormWidth(Window.Sizes.width, Window.Sizes.height) |> dispatch;
      Some(
        () => {
          testId;
          formId;
        },
      );
    }
  );
  let handleResize = event =>
    SettingFormWidth(
      event##currentTarget##innerWidth,
      event##currentTarget##innerHeight,
    )
    |> dispatch;
  useEffect0(() => {
    let testId = Window.Listeners.add("resize", handleResize, true) |> ignore;
    Some(() => testId);
  });
  let showOpen = useCallback(_ => ShowOpen |> dispatch);
  <>
    {showProgress |> disabledObjects
       ? <ProgressLinear style=progressFixed /> : null}
    <IconButton style=menuButn padding="8" onClick=showOpen>
      <IconAction animation="circleTop" src=menuBlack />
    </IconButton>
    <Drawer
      style=drawerNewTube
      left={state.formWidth < 960 ? "-72" : "0"}
      width="72px"
      height="64"
      location="left">
      <List_>
        <ListItem top="0" right="0" bottom="0" left="0">
          <GridContainer
            backgroundColor="transparent"
            direction="column"
            justify="center"
            alignItem="center">
            <GridItem
              style={ReactDOMRe.Style.make(~height="26px", ())}
              top="0"
              right="0"
              bottom="0"
              left="0"
              enterBackgroundColor="transparent"
              backgroundColor="transparent"
              xs="auto">
              <IconGeneral src=homeBlack />
            </GridItem>
            <GridItem
              top="0"
              right="0"
              bottom="0"
              left="0"
              enterBackgroundColor="transparent"
              backgroundColor="transparent"
              xs="auto">
              <Typography variant="subheading">
                <FormattedMessage id="Path.home" defaultMessage="Home" />
              </Typography>
            </GridItem>
          </GridContainer>
        </ListItem>
      </List_>
    </Drawer>
    <Drawer
      style={ReactDOMRe.Style.combine(
        drawerTube,
        ReactDOMRe.Style.make(
          ~transition={
            state.showOpen
              ? "left 225ms cubic-bezier(0.4, 0, 0.6, 1) 0ms"
              : "left 195ms cubic-bezier(0.4, 0, 0.6, 1) 0ms";
          },
          (),
        ),
      )}
      left={state.showOpen ? "0" : "-240"}
      width="240px"
      height="64"
      location="left">
      <List_>
        <ListItem top="0" right="8" bottom="0" left="8">
          <GridContainer
            backgroundColor="transparent"
            direction="row"
            justify="center"
            alignItem="center">
            <GridItem
              style={ReactDOMRe.Style.make(~height="26px", ())}
              top="0"
              right="22"
              bottom="0"
              left="0"
              enterBackgroundColor="transparent"
              backgroundColor="transparent"
              xs="no">
              <IconGeneral src=homeBlack />
            </GridItem>
            <GridItem
              top="0"
              right="0"
              bottom="0"
              left="0"
              enterBackgroundColor="transparent"
              backgroundColor="transparent"
              xs="auto">
              <Typography variant="subheading">
                <FormattedMessage id="Path.home" defaultMessage="Home" />
              </Typography>
            </GridItem>
          </GridContainer>
        </ListItem>
      </List_>
    </Drawer>
    <main
      style={ReactDOMRe.Style.combine(
        mainTube,
        ReactDOMRe.Style.make(
          ~right="0px",
          ~transition=
            "left 195ms cubic-bezier(0.4, 0, 0.6, 1) 0ms, right 195ms cubic-bezier(0.4, 0, 0.6, 1) 0ms",
          ~bottom={
            bottom |> bottoms;
          },
          (),
        ),
      )}
      className="tubelayout">
      <div style=divScrollbar>
        <div
          style={ReactDOMRe.Style.combine(
            marginAuto,
            ReactDOMRe.Style.make(
              ~width={
                width |> widths;
              },
              ~maxWidth={
                width |> widths;
              },
              ~flexBasis={
                width |> widths;
              },
              (),
            ),
          )}>
          {error |> disabledObjects
             ? <div style=errorForm>
                 <Typography
                   variant="tile"
                   color="rgba(255,0,0,0.8)"
                   fontSize="x-large"
                   noWrap=true>
                   {"UNDEFINED THIS PAGE" |> string}
                 </Typography>
               </div>
             : children}
        </div>
      </div>
    </main>
    <BackgroundBoard
      showBackground={state.showOpen}
      backgroundColor="rgba(0,0,0,0.2)"
      onClick=showOpen
    />
  </>;
};
