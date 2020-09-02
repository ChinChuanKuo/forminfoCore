open React;
open Together;
open ReactIntl;
open Icons;
open Path;
open Data;
open Items;
open Axiosapi;
open Storage;
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

type item = {
  id: string,
  tile: string,
  datetime: string,
  showOther: bool,
};

type state = {
  formLoad: bool,
  showProgress: bool,
  error: bool,
  insert: bool,
  update: bool,
  delete: bool,
  export: bool,
  tabitems: list(tabtitem),
  index: int,
  itemCount: int,
  items: array(item),
  showYoutube: bool,
  youtubeText: string,
};

type action =
  | SettingError
  | SettingFormLoad
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFormPolls(int, array(item))
  | SettingFormItems(int, array(item))
  | ClickItemTab(int)
  | ActionSnackBar(string, bool);

let reducer = (state, action) =>
  switch (action) {
  | SettingError => {...state, error: !state.error}
  | SettingFormLoad => {...state, formLoad: !state.formLoad}
  | ActionShowProgress => {...state, showProgress: !state.showProgress}
  | ActionPermissItems(insert, update, delete, export) => {
      ...state,
      insert,
      update,
      delete,
      export,
    }
  | SettingFormPolls(itemCount, items) => {
      ...state,
      itemCount: state.itemCount + itemCount,
      items: Array.append(state.items, items),
    }
  | SettingFormItems(itemCount, items) => {...state, itemCount, items}
  | ClickItemTab(index) => {
      ...state,
      tabitems:
        List.mapi(
          (i, tabtitem) => {...tabtitem, tabtShow: index == i},
          state.tabitems,
        ),
      index,
    }
  | ActionSnackBar(youtubeText, showYoutube) => {
      ...state,
      youtubeText,
      showYoutube,
    }
  };

let initialState = {
  formLoad: false,
  showProgress: true,
  error: false,
  insert: false,
  update: false,
  delete: false,
  export: false,
  tabitems: [
    {tabtShow: false, tabImage: storeBlack, tabPath: proformPath},
    {tabtShow: false, tabImage: menuBookBlack, tabPath: protourPath},
  ],
  index: 0,
  itemCount: 0,
  items: [||],
  showYoutube: false,
  youtubeText: "",
};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);

  let barShowRestoreAction = youtubeText => {
    ActionSnackBar(youtubeText, true) |> dispatch;
    Js.Global.setTimeout(() => ActionSnackBar("", false) |> dispatch, 5000)
    |> ignore;
  };

  let pollingFunc: (int, int) => unit = [%bs.raw
    (length, count) => {| if (!state.showFull) { pollingAJax(length + count); } |}
  ];

  let pollingEror: int => unit = [%bs.raw
    length => {| if (!state.showFull) { setTimeout(() => pollingAJax(length), 15000); } |}
  ];

  let pollingAJax = length =>
    Js.Promise.(
      otherData("newid" |> Locals.select, length)
      |> Axiosapi.Proform.polling
      |> then_(response =>
           {
             SettingFormPolls(
               response##data##items |> Js_array.length,
               response##data##items,
             )
             |> dispatch;
             response##data##items |> Js_array.length |> pollingFunc(length);
           }
           |> resolve
         )
      |> catch(_ => length |> pollingEror |> resolve)
      |> ignore
    );

  let searchAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Axiosapi.Proform.search
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               SettingFormItems(
                 response##data##itemCount,
                 response##data##items,
               )
               |> dispatch;
               ActionShowProgress |> dispatch;
               response##data##itemCount |> pollingAJax;
             | _ =>
               SettingError |> dispatch;
               response##data##status
               |> Status.statusModule
               |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let permissAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Form.permiss
      |> then_(response =>
           {
             ActionPermissItems(
               response##data##insert,
               response##data##update,
               response##data##delete,
               response##data##export,
             )
             |> dispatch;
             searchAJax();
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  useEffect(() =>
    switch (state.formLoad) {
    | true => Some(() => "action" |> Js.log)
    | _ =>
      let testtime = SettingFormLoad |> dispatch;
      let timeId = permissAJax();
      Some(
        () => {
          testtime;
          timeId;
        },
      );
    }
  );

  let clickItemTab =
    useCallback((i, tabPath) => {
      ClickItemTab(i) |> dispatch;
      tabPath |> ReasonReactRouter.push;
    });

  let clickFormBoard = useCallback(id => ActionShowProgress |> dispatch);

  <>
    <NewFacetube showProgress={state.showProgress} error={state.error}>
      <GridItem
        style=marginAuto top="0" right="32" bottom="0" left="32" xs="12">
        <GridContainer direction="column" justify="center" alignItem="stretch">
          <GridItem top="0" right="24" bottom="0" left="24" xs="auto">
            <Tabs id="bus-" index={state.index} short=20 height="3">
              {state.tabitems
               |> List.mapi((i, tabtitem) =>
                    <Tab
                      tabShow={tabtitem.tabtShow}
                      maxWidth="111.6"
                      borderRadius="15"
                      id={"bus-" ++ string_of_int(i)}
                      animationName="none"
                      onClick={_ => tabtitem.tabPath |> clickItemTab(i)}>
                      <IconAction
                        width="28"
                        height="28"
                        animation="leftRight"
                        src={tabtitem.tabImage}
                      />
                    </Tab>
                  )
               |> Array.of_list
               |> array}
            </Tabs>
          </GridItem>
          <GridItem right="24" bottom="0" left="24" xs="auto">
            <GridContainer direction="row" justify="start" alignItem="center">
              {state.items
               |> Array.map(item =>
                    <div onClick={_ => item.id |> clickFormBoard}>
                      <GridItem
                        style={ReactDOMRe.Style.make(
                          ~height="246px",
                          ~marginRight="12px",
                          (),
                        )}
                        top="0"
                        right="0"
                        bottom="0"
                        left="0"
                        width="210px"
                        cursor="pointer"
                        enterBorderWidth="2"
                        borderWidth="2"
                        enterBorderColor="rgba(255,0,0,0.8)"
                        borderRadius="1"
                        xs="no">
                        <Card>
                          <GridContainer
                            direction="column"
                            justify="center"
                            alignItem="stretch">
                            <GridItem
                              top="0" right="0" bottom="0" left="0" xs="auto">
                              <div
                                style={ReactDOMRe.Style.make(
                                  ~height="175px",
                                  (),
                                )}
                              />
                            </GridItem>
                            <GridItem
                              top="0" right="12" bottom="0" left="16" xs="no">
                              <Typography variant="subtitle1">
                                {item.tile |> string}
                              </Typography>
                            </GridItem>
                            <GridItem
                              top="0" right="12" bottom="0" left="16" xs="no">
                              <GridContainer
                                direction="row"
                                justify="center"
                                alignItem="center">
                                <GridItem
                                  top="0"
                                  right="8"
                                  bottom="0"
                                  left="0"
                                  xs="no">
                                  <IconAction
                                    animation="leftRight"
                                    src=dateRangeBlack
                                  />
                                </GridItem>
                                <GridItem
                                  top="0"
                                  right="0"
                                  bottom="0"
                                  left="0"
                                  xs="auto">
                                  <Typography variant="subtitle2">
                                    {item.datetime |> string}
                                  </Typography>
                                </GridItem>
                                <GridItem
                                  top="0"
                                  right="0"
                                  bottom="0"
                                  left="0"
                                  xs="no">
                                  <IconButton
                                    padding="3" disabled={state.showProgress}>
                                    <Tooltip
                                      location="top"
                                      backgroundColor="rgba(255,0,0,0.8)">
                                      <FormattedMessage
                                        id="more"
                                        defaultMessage="More"
                                      />
                                    </Tooltip>
                                    <IconAction
                                      animation="leftRight"
                                      src=moreVertBlack
                                    />
                                  </IconButton>
                                </GridItem>
                              </GridContainer>
                            </GridItem>
                          </GridContainer>
                        </Card>
                      </GridItem>
                    </div>
                  )
               |> array}
            </GridContainer>
          </GridItem>
        </GridContainer>
      </GridItem>
    </NewFacetube>
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {state.youtubeText |> string} </span>, null)
    </SnackbarYoutube>
  </>;
};
