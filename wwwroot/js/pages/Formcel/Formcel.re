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
  showDrop: bool,
  showFile: bool,
  showYoutube: bool,
  youtubeText: string,
};

type action =
  | SettingError
  | SettingFormLoad
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | ShowDrop(bool)
  | ShowFile
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
  | ShowDrop(showDrop) => {...state, showDrop}
  | ShowFile => {...state, showFile: !state.showFile}
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
  showDrop: false,
  showFile: false,
  showYoutube: false,
  youtubeText: "",
};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);

  let fileRef = useRef(Js.Nullable.null);

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

  let dragOver = useCallback(_ => ShowDrop(true) |> dispatch);

  let dragLeave = useCallback(_ => ShowDrop(false) |> dispatch);

  let dropFile =
    useCallback(value => {
      ActionShowProgress |> dispatch;
      ShowDrop(false) |> dispatch;
    });

  let uploadFile = useCallback(value => ActionShowProgress |> dispatch);

  let chooseFile =
    useCallback(_
      //Documents.GetElementById.make("uploadFile") |> Action.click)
      =>
        switch (fileRef |> Ref.current |> Js.Nullable.toOption) {
        | None => ()
        | Some(el) => el->ReactDOMRe.domElementToObj##click() |> ignore
        }
      );

  <>
    <NewFacetube showProgress={state.showProgress} error={state.error}>
      <GridItem
        style=marginAuto
        top="0"
        right="32"
        bottom="0"
        left="32"
        xs="12"
        maxWidth="770px">
        <GridContainer direction="column" justify="center" alignItem="stretch">
          <GridItem right="24" bottom="0" left="24" xs="auto">
            <GeneralUpload
              webLoad={state.showProgress}
              showDrop={state.showDrop}
              fileRef
              onDragOver=dragOver
              onDragLeave=dragLeave
              onDrop={event =>
                ReactEventRe.Synthetic.nativeEvent(event)##dataTransfer##files[0]
                |> dropFile
              }
              disabled={state.showProgress}
              onClick=chooseFile
              onChange={event =>
                ReactEvent.Form.target(event)##files[0] |> uploadFile
              }
            />
          </GridItem>
          <GridItem right="24" bottom="0" left="24" xs="auto"> null </GridItem>
        </GridContainer>
      </GridItem>
    </NewFacetube>
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {state.youtubeText |> string} </span>, null)
    </SnackbarYoutube>
  </>;
};
