open React;
open Together;
open Icons;
open Path;
open Data;
open Items;
open Axiosapi;
open Storage;
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

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
  showYoutube: bool,
  youtubeText: string,
};

type action =
  | SettingError
  | SettingFormLoad
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
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
    {tabtShow: false, tabImage: descriptionBlack, tabPath: proformPath},
    {tabtShow: false, tabImage: tourBlack, tabPath: protourPath},
  ],
  index: 1,
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
             ActionShowProgress |> dispatch;
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
        </GridContainer>
      </GridItem>
    </NewFacetube>
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {state.youtubeText |> string} </span>, null)
    </SnackbarYoutube>
  </>;
};
