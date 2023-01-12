open React;
open Together;
open ReactIntl;
open Icons;
open Data;
open Items;
open Axiosapi;
open Storage;
open OutSide;
open IconAnimation;
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

type answeritem = {
  id: int,
  values: string,
  showAnswer: bool,
  showRight: bool,
};

type formitem = {
  iid: string,
  title: string,
  showVeri: bool,
  showDrop: bool,
  showFile: bool,
  outValue: string,
  value: string,
  showMenu: bool,
  type_: string,
  operation: string,
  area: string,
  eror: string,
  answer: bool,
  showCheck: bool,
  answeritems: array(answeritem),
};

type item = {
  id: string,
  tile: string,
  datetime: string,
  showOther: bool,
  showFinish: bool,
};

type state = {
  formLoad: bool,
  formWidth: int,
  formHeight: int,
  showProgress: bool,
  error: bool,
  insert: bool,
  update: bool,
  delete: bool,
  export: bool,
  itemCount: int,
  items: array(item),
  showFull: bool,
  formId: string,
  formTile: string,
  formDesc: string,
  tabitems: list(tabitem),
  index: int,
  formExam: bool,
  formRestart: bool,
  formFinish: bool,
  formScore: string,
  formitems: array(formitem),
  showYoutube: bool,
  youtubeText: string,
};

type action =
  | SettingError
  | SettingFormLoad
  | SettingFormWidth(int, int)
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFormPolls(int, array(item))
  | SettingFormItems(int, array(item))
  | ClickItemTab(int)
  | ShowAnimationFull(
      string,
      string,
      string,
      bool,
      bool,
      bool,
      string,
      array(formitem),
    )
  | SettingAnimationFull(
      string,
      string,
      string,
      bool,
      bool,
      bool,
      string,
      array(formitem),
    )
  | ShowDrop(bool, int)
  | ShowFile(string, int)
  | ChangeValue(string, int)
  | ShowMenu(int)
  | ClickMenu(string, int)
  | ClickCheckbox(int, int)
  | ClickRadio(int, int)
  | CloseAnimationFull
  | ActionSnackBar(string, bool);

let reducer = (state, action) =>
  switch (action) {
  | SettingError => {...state, error: !state.error}
  | SettingFormLoad => {...state, formLoad: !state.formLoad}
  | SettingFormWidth(width, height) => {
      ...state,
      formWidth: width,
      formHeight: height,
    }
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
          (i, tabtitem) => {...tabtitem, showTab: index == i},
          state.tabitems,
        ),
      index,
    }
  | ShowAnimationFull(id, tile, desc, exam, restart, finish, score, formitems) => {
      ...state,
      formId: id,
      formTile: tile,
      formDesc: desc,
      formExam: exam,
      formRestart: restart,
      formFinish: finish,
      formScore: score,
      formitems,
      showFull: !state.showFull,
    }
  | SettingAnimationFull(
      id,
      tile,
      desc,
      exam,
      restart,
      finish,
      score,
      formitems,
    ) => {
      ...state,
      formId: id,
      formTile: tile,
      formDesc: desc,
      formExam: exam,
      formRestart: restart,
      formFinish: finish,
      formScore: score,
      formitems,
    }
  | ShowDrop(showDrop, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) => index == i ? {...formitem, showDrop} : formitem,
          state.formitems,
        ),
    }
  | ShowFile(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {...formitem, value, showFile: !formitem.showFile} : formitem,
          state.formitems,
        ),
    }
  | ChangeValue(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) => index == i ? {...formitem, value} : formitem,
          state.formitems,
        ),
    }
  | ShowMenu(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {...formitem, showMenu: !formitem.showMenu} : formitem,
          state.formitems,
        ),
    }
  | ClickMenu(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {...formitem, value, showMenu: !formitem.showMenu} : formitem,
          state.formitems,
        ),
    }
  | ClickCheckbox(aindex, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {
                ...formitem,
                answeritems:
                  Array.mapi(
                    (ai, answeritem) =>
                      aindex == ai
                        ? {...answeritem, showAnswer: !answeritem.showAnswer}
                        : answeritem,
                    formitem.answeritems,
                  ),
              }
              : formitem,
          state.formitems,
        ),
    }
  | ClickRadio(aindex, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {
                ...formitem,
                answeritems:
                  Array.mapi(
                    (ai, answeritem) =>
                      {
                        ...answeritem,
                        showAnswer:
                          aindex == ai ? !answeritem.showAnswer : false,
                      },
                    formitem.answeritems,
                  ),
              }
              : formitem,
          state.formitems,
        ),
    }
  | CloseAnimationFull => {...state, showFull: !state.showFull}
  | ActionSnackBar(youtubeText, showYoutube) => {
      ...state,
      youtubeText,
      showYoutube,
    }
  };

let initialState = {
  formLoad: false,
  formWidth: 0,
  formHeight: 0,
  showProgress: true,
  error: false,
  insert: false,
  update: false,
  delete: false,
  export: false,
  itemCount: 0,
  items: [||],
  showFull: false,
  formId: "",
  formTile: "",
  formDesc: "",
  tabitems: [
    {showTab: false, tabImage: storeBlack},
    {showTab: false, tabImage: noteBlack},
  ],
  index: 0,
  formExam: false,
  formRestart: false,
  formFinish: false,
  formScore: "0",
  formitems: [||],
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

  let pollingFunc: (int, int) => unit = [%bs.raw
    (length, count) => {| if (!state.showFull) { pollingAJax(length + count); } |}
  ];

  let pollingEror: int => unit = [%bs.raw
    length => {| if (!state.showFull) { setTimeout(() => pollingAJax(length), 15000); } |}
  ];

  let pollingAJax = length =>
    Js.Promise.(
      length
      |> otherData("newid" |> Locals.select)
      |> Default.polling
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
      |> Default.search
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
             | _ =>
               response##data##status
               |> Status.statusModule
               |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             };
             response##data##itemCount |> pollingAJax;
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
      let sizeId =
        SettingFormWidth(Window.Sizes.width, Window.Sizes.height) |> dispatch;
      let timeId = permissAJax();
      Some(
        () => {
          testtime;
          sizeId;
          timeId;
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

  /*let scrollFunc: 'a => unit = [%bs.raw
      func => {| func(state.items.length); |}
    ];

    let handleScrollBar = event =>
      if (event##target##scrollTop
          ++
          event##target##clientHeight ==
          event##target##scrollHeight) {
        ActionShowProgress |> dispatch;
        scrollAJax |> scrollFunc;
      };*/

  useEffect0(() => {
    let sizeId = Window.Listeners.add("resize", handleResize, true) |> ignore;
    /*let scrollId =
      Window.Listeners.add("scroll", handleScrollBar, true) |> ignore;*/
    Some(() => sizeId);
  });

  let sItemAJax = id =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(id)
      |> Default.sItem
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowAnimationFull(
                 response##data##formId,
                 response##data##tile,
                 response##data##desc,
                 response##data##exam,
                 response##data##restart,
                 response##data##finish,
                 response##data##score,
                 response##data##items,
               )
               |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status
               |> Status.statusModule
               |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickFormBoard =
    useCallback(id => {
      ActionShowProgress |> dispatch;
      id |> sItemAJax;
    });

  let clickItemTab = useCallback(i => ClickItemTab(i) |> dispatch);

  let uploadAJax = files => {
    let formData = FormData.make();
    FormData.append(formData, "file", files) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" => ActionShowProgress |> dispatch
             | _ =>
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
  };

  let dragOver =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowDrop(true, i) |> dispatch;
    });

  let dragLeave =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowDrop(false, i) |> dispatch;
    });

  let dropFile =
    useCallback((event, value, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowDrop(false, i) |> dispatch;
    });

  let uploadFile = useCallback((value, i) => ActionShowProgress |> dispatch);

  let chooseFile =
    useCallback(_
      //Documents.GetElementById.make("uploadFile") |> Action.click)
      =>
        switch (fileRef |> Ref.current |> Js.Nullable.toOption) {
        | None => ()
        | Some(el) => el->ReactDOMRe.domElementToObj##click() |> ignore
        }
      );

  let changeValue =
    useCallback((value, i) => ChangeValue(value, i) |> dispatch);

  let showMenu = useCallback(i => ShowMenu(i) |> dispatch);

  let clickMenu = useCallback((value, i) => ClickMenu(value, i) |> dispatch);

  let clickElement =
    useCallback((value, ai, i) =>
      switch (value) {
      | "checkbox" => ClickCheckbox(ai, i) |> dispatch
      | _ => ClickRadio(ai, i) |> dispatch
      }
    );

  let restartAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(state.formId)
      |> Default.restart
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               SettingAnimationFull(
                 response##data##formId,
                 response##data##tile,
                 response##data##desc,
                 response##data##exam,
                 response##data##restart,
                 response##data##finish,
                 response##data##score,
                 response##data##items,
               )
               |> dispatch;
               ClickItemTab(0) |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status
               |> Status.statusModule
               |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let restartForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      restartAJax();
    });

  let insertAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> iFormData(state.formId, state.formitems)
      |> Default.insert
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               SettingAnimationFull(
                 response##data##formId,
                 response##data##tile,
                 response##data##desc,
                 response##data##exam,
                 response##data##restart,
                 response##data##finish,
                 response##data##score,
                 response##data##items,
               )
               |> dispatch;
               ClickItemTab(1) |> dispatch;
               "saveSuccess" |> Status.statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status
               |> Status.statusModule
               |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let insertForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      insertAJax();
    });

  let closeAnimationFull = useCallback(_ => CloseAnimationFull |> dispatch);

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
                              top="0"
                              right="12"
                              bottom="0"
                              left="16"
                              width="180px"
                              xs="no">
                              <Typography variant="subtitle1" noWrap=true>
                                {item.tile |> string}
                              </Typography>
                            </GridItem>
                            <GridItem
                              top="0"
                              right="12"
                              bottom="0"
                              left="16"
                              width="180px"
                              xs="no">
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
    <DialogFull showAnimation={state.showFull}>
      <DialogTitle top="20" left="64">
        <Typography variant="tile"> {state.formTile |> string} </Typography>
      </DialogTitle>
      <DialogContent>
        <DialogContentText>
          <GridItem
            style=marginAuto
            top="0"
            right="0"
            bottom="0"
            left="54"
            xs="12"
            maxWidth="770px">
            <GridContainer
              direction="column" justify="center" alignItem="stretch">
              <GridItem
                style={ReactDOMRe.Style.make(
                  ~position="sticky",
                  ~top="0px",
                  ~zIndex="1000",
                  (),
                )}
                top="0"
                right="24"
                left="24"
                xs="auto">
                <GridContainer
                  direction="row" justify="around" alignItem="center">
                  <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                    <Tabs id="report-" index={state.index} height="3">
                      {state.tabitems
                       |> List.mapi((i, tabitem) =>
                            <Tab
                              showTab={tabitem.showTab}
                              maxWidth="111.6"
                              borderRadius="15"
                              id={"report-" ++ string_of_int(i)}
                              animationName="none"
                              onClick={_ => i |> clickItemTab}>
                              <IconAction
                                width="28"
                                height="28"
                                animation="leftRight"
                                src={tabitem.tabImage}
                              />
                            </Tab>
                          )
                       |> Array.of_list
                       |> array}
                    </Tabs>
                  </GridItem>
                  {switch (
                     state.formFinish,
                     state.formRestart,
                     state.formExam,
                   ) {
                   | (true, true, true) =>
                     <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                       <Button
                         disabled={state.showProgress} onClick=restartForm>
                         <IconAction animation="leftRight" src=refreshWhite />
                         <FormattedMessage
                           id="Formor.restart"
                           defaultMessage="Restart"
                         />
                       </Button>
                     </GridItem>
                   | (false, _, true) =>
                     <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                       <Button
                         disabled={state.showProgress} onClick=insertForm>
                         <IconAction animation="leftRight" src=sendWhite />
                         <FormattedMessage
                           id="Default.send"
                           defaultMessage="Send"
                         />
                       </Button>
                     </GridItem>
                   | (_, _, false) =>
                     <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                       <Button
                         disabled={state.showProgress} onClick=insertForm>
                         <IconAction animation="leftRight" src=saveWhite />
                         <FormattedMessage id="save" defaultMessage="Save" />
                       </Button>
                     </GridItem>
                   | (_, _, _) => null
                   }}
                </GridContainer>
              </GridItem>
              {switch (state.index) {
               | 0 =>
                 <>
                   <GridItem top="6" right="27" left="27" xs="auto">
                     <Typography variant="subheading">
                       {state.formDesc |> string}
                     </Typography>
                   </GridItem>
                   {state.formitems
                    |> Array.mapi((i, formitem) =>
                         <GridItem top="0" right="24" left="24" xs="auto">
                           <CardOrPaperBoard
                             showLine=true showAnswer={formitem.answer}>
                             <GridContainer
                               direction="column"
                               justify="start"
                               alignItem="stretch">
                               <GridItem right="20" left="20" xs="auto">
                                 <Typography
                                   variant="subheading"
                                   fontSize="1.2rem"
                                   fontWeight="bolder">
                                   {formitem.title |> string}
                                 </Typography>
                               </GridItem>
                               <GridItem top="0" bottom="0" xs="auto">
                                 {switch (formitem.outValue) {
                                  | "label" =>
                                    <Typography
                                      variant="subtitle2"
                                      style={ReactDOMRe.Style.make(
                                        ~paddingLeft="6px",
                                        ~paddingRight="6px",
                                        (),
                                      )}
                                      noWrap=true>
                                      null
                                    </Typography>
                                  | "image" =>
                                    <ImageUpload
                                      webLoad={state.showProgress}
                                      showDrop={formitem.showDrop}
                                      showFile={formitem.showFile}
                                      src={formitem.value}
                                      fileRef
                                      onDragOver={event =>
                                        i |> dragOver(event)
                                      }
                                      onDragLeave={event =>
                                        i |> dragLeave(event)
                                      }
                                      onDrop={event =>
                                        i
                                        |> dropFile(
                                             event,
                                             ReactEventRe.Synthetic.nativeEvent(
                                               event,
                                             )##dataTransfer##files[0],
                                           )
                                      }
                                      disabled={state.showProgress}
                                      onClick=chooseFile
                                      onChange={event =>
                                        i
                                        |> uploadFile(
                                             ReactEvent.Form.target(event)##files[0],
                                           )
                                      }
                                    />
                                  | "text" =>
                                    <TextFieldStandard
                                      width="50"
                                      top="0"
                                      enterBorderColor="rgba(255,0,0,0.8)"
                                      downBorderColor="rgba(255,0,0,0.6)"
                                      borderColor="rgba(0,0,0,0.2)"
                                      value={formitem.value}
                                      disabled={state.showProgress}
                                      onChange={event =>
                                        i
                                        |> changeValue(
                                             ReactEvent.Form.target(event)##value,
                                           )
                                      }>
                                      null
                                    </TextFieldStandard>
                                  | "textarea" =>
                                    <TextFieldStandard
                                      top="0"
                                      enterBorderColor="rgba(255,0,0,0.8)"
                                      downBorderColor="rgba(255,0,0,0.6)"
                                      borderColor="rgba(0,0,0,0.2)"
                                      value={formitem.value}
                                      disabled={state.showProgress}
                                      onChange={event =>
                                        i
                                        |> changeValue(
                                             ReactEvent.Form.target(event)##value,
                                           )
                                      }>
                                      null
                                    </TextFieldStandard>
                                  | "textline" =>
                                    <TextFieldMultiline
                                      top="12"
                                      bottom="12"
                                      labelColor="rgba(255,0,0,0.8)"
                                      borderTop="10"
                                      borderBottom="10"
                                      enterBorderColor="rgba(255,0,0,0.8)"
                                      downBorderColor="rgba(255,0,0,0.6)"
                                      borderColor="rgba(0,0,0,0.2)"
                                      rows=3
                                      value={formitem.value}
                                      disabled={state.showProgress}
                                      onChange={event =>
                                        i
                                        |> changeValue(
                                             ReactEvent.Form.target(event)##value,
                                           )
                                      }>
                                      null
                                    </TextFieldMultiline>
                                  | "droplist" =>
                                    <>
                                      <SelectStandard
                                        top="12"
                                        right="10"
                                        bottom="10"
                                        left="10"
                                        enterBorderColor="rgba(255,0,0,0.8)"
                                        downBorderColor="rgba(255,0,0,0.6)"
                                        borderColor="rgba(0,0,0,0.2)"
                                        value={formitem.value}
                                        disabled={state.showProgress}
                                        onClick={_ => i |> showMenu}>
                                        ...(
                                             formitem.showMenu
                                               ? <SelectMenu
                                                   top="50%"
                                                   transform="translate(0, -50%)"
                                                   maxHeight="280"
                                                   minHeight="0"
                                                   topLeft="12"
                                                   topRight="12"
                                                   bottomRight="12"
                                                   bottomLeft="12"
                                                   paddingRight="8"
                                                   paddingLeft="8">
                                                   {formitem.answeritems
                                                    |> Array.map(answeritem =>
                                                         <MenuItem
                                                           top="0"
                                                           right="8"
                                                           bottom="0"
                                                           left="8"
                                                           topLeft="12"
                                                           topRight="12"
                                                           bottomRight="12"
                                                           bottomLeft="12"
                                                           onClick={_ =>
                                                             i
                                                             |> clickMenu(
                                                                  answeritem.
                                                                    values,
                                                                )
                                                           }>
                                                           {answeritem.values
                                                            |> string}
                                                         </MenuItem>
                                                       )
                                                    |> array}
                                                 </SelectMenu>
                                               : null,
                                             <IconGeneral
                                               animation={
                                                 formitem.showMenu
                                                 |> topDownRorate
                                               }
                                               src=arrowDownBlack
                                             />,
                                           )
                                      </SelectStandard>
                                      <BackgroundBoard
                                        showBackground={formitem.showMenu}
                                        backgroundColor="transparent"
                                        onClick={_ => i |> showMenu}
                                      />
                                    </>
                                  | _ =>
                                    <GridContainer
                                      direction="column"
                                      justify="center"
                                      alignItem="stretch">
                                      {formitem.answeritems
                                       |> Array.mapi((ai, answeritem) =>
                                            <GridItem
                                              top="0"
                                              bottom="6"
                                              left="0"
                                              right="0"
                                              xs="auto">
                                              <GridContainer
                                                direction="row"
                                                justify="start"
                                                alignItem="center">
                                                <GridItem
                                                  top="0"
                                                  right="0"
                                                  bottom="0"
                                                  left="0"
                                                  xs="no">
                                                  <IconButton
                                                    padding="4"
                                                    disabled={
                                                               state.
                                                                 showProgress
                                                             }
                                                    onClick={_ =>
                                                      i
                                                      |> clickElement(
                                                           formitem.outValue,
                                                           ai,
                                                         )
                                                    }>
                                                    <IconAction
                                                      animation="leftRight"
                                                      src={
                                                        answeritem.showAnswer
                                                        |> answerIcon(
                                                             formitem.outValue,
                                                           )
                                                      }
                                                    />
                                                  </IconButton>
                                                </GridItem>
                                                <GridItem
                                                  top="0"
                                                  right="6"
                                                  bottom="0"
                                                  left="0"
                                                  xs="auto">
                                                  <Typography
                                                    variant="subtitle1">
                                                    {answeritem.values
                                                     |> string}
                                                  </Typography>
                                                </GridItem>
                                                {switch (
                                                   state.formFinish,
                                                   state.formExam,
                                                   answeritem.showRight,
                                                 ) {
                                                 | (true, true, true) =>
                                                   <GridItem
                                                     top="0"
                                                     right="0"
                                                     bottom="0"
                                                     left="0"
                                                     xs="no">
                                                     <IconAction
                                                       animation="leftRight"
                                                       src=doneSuccessful
                                                     />
                                                   </GridItem>
                                                 | (_, _, _) => null
                                                 }}
                                              </GridContainer>
                                            </GridItem>
                                          )
                                       |> array}
                                    </GridContainer>
                                  }}
                               </GridItem>
                             </GridContainer>
                           </CardOrPaperBoard>
                         </GridItem>
                       )
                    |> array}
                 </>
               | _ =>
                 <div style=errorForm>
                   {switch (state.formFinish, state.formExam) {
                    | (true, true) =>
                      <Typography
                        variant="h1"
                        color="rgba(255,0,0,0.8)"
                        fontWeight="bolder">
                        {state.formScore |> string}
                      </Typography>
                    | (_, true) =>
                      <Typography
                        variant="tile"
                        color="rgba(255,0,0,0.8)"
                        fontSize="x-large"
                        fontWeight="bolder">
                        {"THIS FORM UNEXAM" |> string}
                      </Typography>
                    | (_, false) =>
                      <Typography
                        variant="tile"
                        color="rgba(255,0,0,0.8)"
                        fontSize="x-large"
                        fontWeight="bolder">
                        {"THIS FORM IS NOT EXAM" |> string}
                      </Typography>
                    }}
                 </div>
               }}
            </GridContainer>
          </GridItem>
        </DialogContentText>
      </DialogContent>
      <DialogActions>
        <div
          style={ReactDOMRe.Style.make(
            ~position="fixed",
            ~top="10px",
            ~left="10px",
            (),
          )}>
          <IconButton
            padding="12"
            disabled={state.showProgress}
            onClick=closeAnimationFull>
            <Tooltip location="bottom" backgroundColor="rgba(255,0,0,0.8)">
              <FormattedMessage id="closed" defaultMessage="Closed" />
            </Tooltip>
            <IconAction animation="circle" src=clearBlack />
          </IconButton>
        </div>
      </DialogActions>
    </DialogFull>
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {state.youtubeText |> string} </span>, null)
    </SnackbarYoutube>
  </>;
};
