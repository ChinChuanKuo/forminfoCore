open React;
open Together;
open ReactIntl;
open Icons;
open Path;
open Data;
open Items;
open Axiosapi;
open Storage;
open AnswerColor;
open SwitchColor;
open IconAnimation;
open ObjectFormat;
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

type operitem = {
  newid: string,
  userid: string,
  name: string,
  showOper: bool,
};

type dertitem = {
  showPanel: bool,
  dertment: string,
  operitems: array(operitem),
  dertModify: bool,
};

type settitem = {
  stdate: string,
  sttime: string,
  endate: string,
  entime: string,
  showExam: bool,
  randOption: bool,
  randSubtile: bool,
  showRestart: bool,
  showLimit: bool,
  dertitems: array(dertitem),
  number: string,
};

type viewitem = {
  vnewid: string,
  vuserid: string,
  vname: string,
  writed: string,
  score: string,
};

type answeritem = {
  id: int,
  value: string,
  showAnswer: bool,
  ansrDelete: bool,
  ansrModify: bool,
  ansrCreate: bool,
};

type formitem = {
  iid: int,
  showLine: bool,
  title: string,
  showOut: bool,
  showVeri: bool,
  showDrop: bool,
  showFile: bool,
  outValue: string,
  type_: string,
  showType: bool,
  typeitems: array(optionitem),
  operation: string,
  showOperation: bool,
  operationitems: array(optionitem),
  area: string,
  eror: string,
  showCheck: bool,
  showMore: bool,
  opticonitems: array(opticonitem),
  answeritems: array(answeritem),
  formDelete: bool,
  formModify: bool,
  formCreate: bool,
};

type item = {
  id: string,
  tile: string,
  datetime: string,
  showOther: bool,
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
  tabitems: list(tabtitem),
  index: int,
  itemCount: int,
  items: array(item),
  showRight: bool,
  showDrop: bool,
  showFile: bool,
  showFull: bool,
  formId: string,
  formTile: string,
  formDesc: string,
  formtabitems: list(tabitem),
  formindex: int,
  formitems: array(formitem),
  settitems: array(settitem),
  viewitems: array(viewitem),
  showYoutube: bool,
  youtubeText: string,
};

let newitem = (iid, opticonitems) => [|
  {
    iid,
    showLine: false,
    title: "",
    showOut: false,
    showVeri: false,
    showDrop: false,
    showFile: false,
    outValue: "radio",
    type_: "",
    showType: false,
    typeitems: [||],
    operation: "",
    showOperation: false,
    operationitems: [||],
    area: "",
    eror: "",
    showCheck: false,
    showMore: false,
    opticonitems,
    answeritems: [|
      {
        id: 1,
        value: "",
        showAnswer: false,
        ansrDelete: false,
        ansrModify: false,
        ansrCreate: true,
      },
    |],
    formDelete: false,
    formModify: false,
    formCreate: true,
  },
|];

let newansweritem = id => [|
  {
    id,
    value: "",
    showAnswer: false,
    ansrDelete: false,
    ansrModify: false,
    ansrCreate: true,
  },
|];

type action =
  | SettingError
  | SettingFormLoad
  | SettingFormWidth(int, int)
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFormPolls(int, array(item))
  | SettingFormItems(int, array(item))
  | SettingSettItems(array(settitem))
  | ClickItemTab(int)
  | ShowAnimationRight
  | ShowDrop(bool)
  | ShowFile
  | CloseAnimationRight
  | ShowAnimationFull(
      string,
      string,
      string,
      array(formitem),
      array(settitem),
    )
  | SettingViewItems(array(viewitem))
  | ShowOther(int)
  | ChangeFormTile(string)
  | ChangeFormDesc(string)
  | ClickFormTab(int)
  | ClickBoardPaper(int)
  | ChangeTile(string, int)
  | ShowOut(int)
  | ShowValue(string, int)
  | ChangeText(string, int, int)
  | ClickRadio(int, int)
  | ClickCheckbox(int, int)
  | ClearOption(int, int)
  | ShowType(int)
  | ClickType(string, string, array(optionitem), int)
  | ShowOperation(int)
  | ClickOperation(string, int)
  | ChangeArea(string, int)
  | ChangeEror(string, int)
  | ClearCondition(int)
  | ShowMore(int)
  | ShowItemVerification(
      string,
      array(optionitem),
      string,
      array(optionitem),
      int,
    )
  | CheckItem(int)
  | DeleteItem(int)
  | AddItem(int)
  | AddForm(array(opticonitem))
  | DeleteForm(string)
  | ChangeStdate(string, int)
  | ChangeSttime(string, int)
  | ChangeEndate(string, int)
  | ChangeEntime(string, int)
  | ShowExam(int)
  | RandOption(int)
  | RandSubtile(int)
  | ShowRestart(int)
  | ChangeNumber(string, int)
  | ShowLimit(int)
  | AddDert(int, array(dertitem))
  | ShowPanel(int, int)
  | AddOper(int, int, array(operitem))
  | ShowOper(int, int, int)
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
  | SettingSettItems(settitems) => {...state, settitems}
  | ClickItemTab(index) => {
      ...state,
      tabitems:
        List.mapi(
          (i, tabtitem) => {...tabtitem, showTabt: index == i},
          state.tabitems,
        ),
      index,
    }
  | ShowAnimationRight => {
      ...state,
      showDrop: false,
      showFile: false,
      showRight: !state.showRight,
    }
  | ShowDrop(showDrop) => {...state, showDrop}
  | ShowFile => {...state, showFile: !state.showFile}
  | CloseAnimationRight => {...state, showRight: !state.showRight}
  | ShowAnimationFull(id, tile, desc, formitems, settitems) => {
      ...state,
      formId: id,
      formTile: tile,
      formDesc: desc,
      formitems,
      settitems,
      formindex: 0,
      showFull: !state.showFull,
    }
  | SettingViewItems(viewitems) => {...state, viewitems}
  | ShowOther(index) => {
      ...state,
      items:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {...formitem, showOther: !formitem.showOther} : formitem,
          state.items,
        ),
    }
  | ChangeFormTile(value) => {...state, formTile: value}
  | ChangeFormDesc(value) => {...state, formDesc: value}
  | ClickFormTab(index) => {
      ...state,
      formtabitems:
        List.mapi(
          (i, tabitem) => {...tabitem, showTab: index == i},
          state.formtabitems,
        ),
      formindex: index,
    }
  | ClickBoardPaper(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => {...item, showLine: index == i},
          state.formitems,
        ),
    }
  | ChangeTile(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {...formitem, title: value, formModify: true} : formitem,
          state.formitems,
        ),
    }
  | ShowOut(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            {...formitem, showOut: index == i ? !formitem.showOut : false},
          state.formitems,
        ),
    }
  | ShowValue(outValue, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {...formitem, outValue, showOut: false, formModify: true}
              : formitem,
          state.formitems,
        ),
    }
  | ChangeText(value, rindex, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {
                ...formitem,
                answeritems:
                  Array.mapi(
                    (ri, answeritem) =>
                      rindex == ri
                        ? {...answeritem, value, ansrModify: true}
                        : answeritem,
                    formitem.answeritems,
                  ),
                formModify: true,
              }
              : formitem,
          state.formitems,
        ),
    }
  | ClickRadio(rindex, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {
                ...formitem,
                answeritems:
                  Array.mapi(
                    (ri, answeritem) =>
                      {
                        ...answeritem,
                        showAnswer:
                          rindex == ri ? !answeritem.showAnswer : false,
                        ansrModify: true,
                      },
                    formitem.answeritems,
                  ),
                formModify: true,
              }
              : formitem,
          state.formitems,
        ),
    }
  | ClickCheckbox(rindex, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {
                ...formitem,
                answeritems:
                  Array.mapi(
                    (ri, answeritem) =>
                      rindex == ri
                        ? {
                          ...answeritem,
                          showAnswer: !answeritem.showAnswer,
                          ansrModify: true,
                        }
                        : answeritem,
                    formitem.answeritems,
                  ),
                formModify: true,
              }
              : formitem,
          state.formitems,
        ),
    }
  | ClearOption(rindex, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {
                ...formitem,
                answeritems:
                  Array.mapi(
                    (ri, answeritem) =>
                      rindex == ri
                        ? {...answeritem, ansrDelete: !answeritem.ansrDelete}
                        : answeritem,
                    formitem.answeritems,
                  ),
                formModify: true,
              }
              : formitem,
          state.formitems,
        ),
    }
  | ShowType(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {...formitem, showType: !formitem.showType} : formitem,
          state.formitems,
        ),
    }
  | ClickType(type_, operation, operationitems, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {
                ...formitem,
                type_,
                operation,
                operationitems,
                showType: false,
                formModify: true,
              }
              : formitem,
          state.formitems,
        ),
    }
  | ShowOperation(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {...formitem, showOperation: !formitem.showOperation}
              : formitem,
          state.formitems,
        ),
    }
  | ClickOperation(operation, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {
                ...formitem,
                operation,
                showOperation: false,
                formModify: true,
              }
              : formitem,
          state.formitems,
        ),
    }
  | ChangeArea(area, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i ? {...formitem, area, formModify: true} : formitem,
          state.formitems,
        ),
    }
  | ChangeEror(eror, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i ? {...formitem, eror, formModify: true} : formitem,
          state.formitems,
        ),
    }
  | ClearCondition(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {...formitem, showVeri: false, showMore: false} : formitem,
          state.formitems,
        ),
    }
  | ShowMore(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {...formitem, showMore: !formitem.showMore} : formitem,
          state.formitems,
        ),
    }
  | ShowItemVerification(type_, typeitems, operation, operationitems, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {
                ...formitem,
                type_,
                typeitems,
                operation,
                operationitems,
                showVeri: true,
                showMore: false,
                formModify: true,
              }
              : formitem,
          state.formitems,
        ),
    }
  | CheckItem(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {...formitem, showCheck: !formitem.showCheck} : formitem,
          state.formitems,
        ),
    }
  | DeleteItem(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {...formitem, formDelete: !formitem.formDelete} : formitem,
          state.formitems,
        ),
    }
  | AddItem(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {
                ...formitem,
                answeritems:
                  Array.append(
                    formitem.answeritems,
                    newansweritem(
                      state.formitems[i].answeritems[Js_array.length(
                                                       formitem.answeritems,
                                                     )
                                                     - 1].
                        id
                      + 1,
                    ),
                  ),
              }
              : formitem,
          state.formitems,
        ),
    }
  | AddForm(opticonitems) => {
      ...state,
      formitems:
        Array.append(
          state.formitems,
          newitem(
            state.formitems[Js_array.length(state.formitems) - 1].iid + 1,
            opticonitems,
          ),
        ),
    }
  | DeleteForm(id) => {
      ...state,
      items: Js_array.filter((item: item) => item.id !== id, state.items),
    }
  | ChangeStdate(value, index) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) =>
            index == i ? {...settitem, stdate: value} : settitem,
          state.settitems,
        ),
    }
  | ChangeSttime(value, index) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) =>
            index == i ? {...settitem, sttime: value} : settitem,
          state.settitems,
        ),
    }
  | ChangeEndate(value, index) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) =>
            index == i ? {...settitem, endate: value} : settitem,
          state.settitems,
        ),
    }
  | ChangeEntime(value, index) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) =>
            index == i ? {...settitem, entime: value} : settitem,
          state.settitems,
        ),
    }
  | ShowExam(index) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) =>
            index == i
              ? {
                ...settitem,
                showExam: !settitem.showExam,
                randOption: settitem.showExam ? false : settitem.randOption,
                randSubtile: settitem.showExam ? false : settitem.randSubtile,
                showRestart: settitem.showExam ? false : settitem.showRestart,
              }
              : settitem,
          state.settitems,
        ),
    }
  | RandOption(index) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) =>
            index == i
              ? {...settitem, randOption: !settitem.randOption} : settitem,
          state.settitems,
        ),
    }
  | RandSubtile(index) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) =>
            index == i
              ? {...settitem, randSubtile: !settitem.randSubtile} : settitem,
          state.settitems,
        ),
    }
  | ShowRestart(index) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) =>
            index == i
              ? {...settitem, showRestart: !settitem.showRestart} : settitem,
          state.settitems,
        ),
    }
  | ChangeNumber(value, index) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) =>
            index == i ? {...settitem, number: value} : settitem,
          state.settitems,
        ),
    }
  | ShowLimit(index) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) =>
            index == i
              ? {...settitem, showLimit: !settitem.showLimit} : settitem,
          state.settitems,
        ),
    }
  | AddDert(index, dertitems) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) => index == i ? {...settitem, dertitems} : settitem,
          state.settitems,
        ),
    }
  | ShowPanel(index, dindex) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) =>
            index == i
              ? {
                ...settitem,
                dertitems:
                  Array.mapi(
                    (di, dertitem) =>
                      dindex == di
                        ? {...dertitem, showPanel: !dertitem.showPanel}
                        : dertitem,
                    settitem.dertitems,
                  ),
              }
              : settitem,
          state.settitems,
        ),
    }
  | AddOper(index, dindex, operitems) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) =>
            index == i
              ? {
                ...settitem,
                dertitems:
                  Array.mapi(
                    (di, dertitem) =>
                      dindex == di ? {...dertitem, operitems} : dertitem,
                    settitem.dertitems,
                  ),
              }
              : settitem,
          state.settitems,
        ),
    }
  | ShowOper(index, dindex, oindex) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) =>
            index == i
              ? {
                ...settitem,
                dertitems:
                  Array.mapi(
                    (di, dertitem) =>
                      dindex == di
                        ? {
                          ...dertitem,
                          operitems:
                            Array.mapi(
                              (oi, operitem) =>
                                oindex == oi
                                  ? {
                                    ...operitem,
                                    showOper: !operitem.showOper,
                                  }
                                  : operitem,
                              dertitem.operitems,
                            ),
                          dertModify: true,
                        }
                        : dertitem,
                    settitem.dertitems,
                  ),
              }
              : settitem,
          state.settitems,
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
  tabitems: [
    {showTabt: false, tabImage: descriptionBlack, tabPath: proformPath},
    {showTabt: false, tabImage: tourBlack, tabPath: protourPath},
  ],
  index: 0,
  itemCount: 0,
  items: [||],
  showRight: false,
  showDrop: false,
  showFile: false,
  showFull: false,
  formId: "",
  formTile: "",
  formDesc: "",
  formtabitems: [
    {showTab: true, tabImage: questionAnswerBlack},
    {showTab: false, tabImage: settingsBlack},
    {showTab: false, tabImage: personAddBlack},
    {showTab: false, tabImage: listBlack},
  ],
  formindex: 0,
  formitems: [||],
  settitems: [||],
  viewitems: [||],
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

  let clickItemTab =
    useCallback((i, tabPath) => {
      ClickItemTab(i) |> dispatch;
      tabPath |> ReasonReactRouter.push;
    });

  let showAnimationRight = useCallback(_ => ShowAnimationRight |> dispatch);

  let settAJax = id =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(id)
      |> Axiosapi.Proform.sett
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               "success" |> Status.uploadModels |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
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

  let uploadAJax = files => {
    let formData = FormData.make();
    FormData.append(formData, "file", files) |> ignore;
    Js.Promise.(
      formData
      |> Excels.upload
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" => response##data##formId |> settAJax
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
    useCallback(event => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowDrop(true) |> dispatch;
    });

  let dragLeave =
    useCallback(event => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowDrop(false) |> dispatch;
    });

  let dropFile =
    useCallback((event, value) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowDrop(false) |> dispatch;
      value |> uploadAJax;
    });

  let uploadFile =
    useCallback(value => {
      ActionShowProgress |> dispatch;
      value |> uploadAJax;
    });

  let chooseFile =
    useCallback(_
      //Documents.GetElementById.make("uploadFile") |> Action.click)
      =>
        switch (fileRef |> Ref.current |> Js.Nullable.toOption) {
        | None => ()
        | Some(el) => el->ReactDOMRe.domElementToObj##click() |> ignore
        }
      );

  let closeAnimationRight = useCallback(_ => CloseAnimationRight |> dispatch);

  let sItemAJax = id =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(id)
      |> Axiosapi.Proform.sItem
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowAnimationFull(
                 response##data##formId,
                 response##data##tile,
                 response##data##desc,
                 response##data##items,
                 response##data##settitems,
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

  let showOther =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowOther(i) |> dispatch;
    });

  let exportForm =
    useCallback((event, id, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowOther(i) |> dispatch;
      "/Excel/excelData?formid="
      ++ id
      ++ "&newid="
      ++ checkObjects("newid" |> Locals.select)
      |> Window.Locations.assign;
    });

  let changeFormTile =
    useCallback(value => ChangeFormTile(value) |> dispatch);

  let changeFormDesc =
    useCallback(value => ChangeFormDesc(value) |> dispatch);

  let sLimitAJax = i =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(state.formId)
      |> Axiosapi.Proform.sLimit
      |> then_(response =>
           {
             AddDert(i, response##data##items) |> dispatch;
             ActionShowProgress |> dispatch;
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let sWriteAJax = i =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(state.formId)
      |> Axiosapi.Proform.sWrite
      |> then_(response =>
           {
             SettingViewItems(response##data##items) |> dispatch;
             ActionShowProgress |> dispatch;
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickFormTab =
    useCallback(i => {
      ClickFormTab(i) |> dispatch;
      if (i == 2 && state.settitems[0].showLimit) {
        ActionShowProgress |> dispatch;
        0 |> sLimitAJax;
      } else if (i == 3) {
        ActionShowProgress |> dispatch;
        0 |> sWriteAJax;
      };
    });

  let clickBoardPaper = useCallback(i => ClickBoardPaper(i) |> dispatch);

  let changeTile =
    useCallback((value, i) => ChangeTile(value, i) |> dispatch);

  let showOut = useCallback(i => ShowOut(i) |> dispatch);

  let showValue = useCallback((value, i) => ShowValue(value, i) |> dispatch);

  let changeText =
    useCallback((value, ri, i) => ChangeText(value, ri, i) |> dispatch);

  let clickElement =
    useCallback((value, ri, i) =>
      switch (value) {
      | "checkbox" => ClickCheckbox(ri, i) |> dispatch
      | _ => ClickRadio(ri, i) |> dispatch
      }
    );

  let clearOption = useCallback((ri, i) => ClearOption(ri, i) |> dispatch);

  let showType = useCallback(i => ShowType(i) |> dispatch);

  let stypeAJax = (type_, i) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> sRowsData(state.formId, type_)
      |> Axiosapi.Proform.sType
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ClickType(
                 type_,
                 response##data##value,
                 response##data##items,
                 i,
               )
               |> dispatch
             | _ =>
               response##data##status
               |> Status.statusModule
               |> barShowRestoreAction;
               ClearCondition(i) |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickType = useCallback((type_, i) => type_ |> stypeAJax(i));

  let showOperation = useCallback(i => ShowOperation(i) |> dispatch);

  let clickOperation =
    useCallback((operation, i) => ClickOperation(operation, i) |> dispatch);

  let changeArea = useCallback((area, i) => ChangeArea(area, i) |> dispatch);

  let changeEror = useCallback((area, i) => ChangeEror(area, i) |> dispatch);

  let clearCondition = useCallback(i => ClearCondition(i) |> dispatch);

  let showMore = useCallback(i => ShowMore(i) |> dispatch);

  let sveriAJax = (id, i) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> sRowsData(state.formId, id)
      |> Axiosapi.Proform.sVeri
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowItemVerification(
                 response##data##type_,
                 response##data##typeitems,
                 response##data##operation,
                 response##data##operationitems,
                 i,
               )
               |> dispatch
             | _ =>
               response##data##status
               |> Status.statusModule
               |> barShowRestoreAction;
               ClearCondition(i) |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let showVerification =
    useCallback((id, showVeri, i) =>
      showVeri ? ClearCondition(i) |> dispatch : id |> sveriAJax(i)
    );

  let checkItem = useCallback(i => CheckItem(i) |> dispatch);

  let deleteItem = useCallback(i => DeleteItem(i) |> dispatch);

  let addItem = useCallback(i => AddItem(i) |> dispatch);

  let insertAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> uFormsData(
           state.formId,
           state.formTile,
           state.formDesc,
           Js_array.filter(
             (formitem: formitem) =>
               formitem.formDelete === true
               || formitem.formModify === true
               || formitem.formCreate === true,
             state.formitems,
           ),
           state.settitems,
           Js_array.filter(
             (dertitem: dertitem) => dertitem.dertModify === true,
             state.settitems[0].dertitems,
           ),
         )
      |> Axiosapi.Proform.insert
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               CloseAnimationFull |> dispatch;
               "saveSuccess" |> Status.statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
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

  let insertForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      insertAJax();
    });

  let addAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Axiosapi.Proform.add
      |> then_(response =>
           {
             AddForm(response##data##items) |> dispatch;
             ActionShowProgress |> dispatch;
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let addForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      addAJax();
    });

  let deleteAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> dFormData(state.formId)
      |> Axiosapi.Proform.delete
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               DeleteForm(state.formId) |> dispatch;
               CloseAnimationFull |> dispatch;
               "deleteSuccess" |> Status.statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
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

  let deleteForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      deleteAJax();
    });

  let changeStdate =
    useCallback((value, i) => ChangeStdate(value, i) |> dispatch);

  let changeSttime =
    useCallback((value, i) => ChangeSttime(value, i) |> dispatch);

  let changeEndate =
    useCallback((value, i) => ChangeEndate(value, i) |> dispatch);

  let changeEntime =
    useCallback((value, i) => ChangeEntime(value, i) |> dispatch);

  let showExam = useCallback(i => ShowExam(i) |> dispatch);

  let randOption = useCallback(i => RandOption(i) |> dispatch);

  let randSubtile = useCallback(i => RandSubtile(i) |> dispatch);

  let showRestart = useCallback(i => ShowRestart(i) |> dispatch);

  let changeNumber =
    useCallback((value, i) => ChangeNumber(value, i) |> dispatch);

  let showLimit =
    useCallback((value, i) => {
      ShowLimit(i) |> dispatch;
      if (!value) {
        ActionShowProgress |> dispatch;
        i |> sLimitAJax;
      };
    });

  let sOperAJax = (value, i, di) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> sRowsData(state.formId, value)
      |> Axiosapi.Proform.sOper
      |> then_(response =>
           AddOper(i, di, response##data##items) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let showPanel =
    useCallback((value, i, di, items) => {
      ShowPanel(i, di) |> dispatch;
      if (items |> Js_array.length == 0) {
        di |> sOperAJax(value, i);
      };
    });

  let showOper = useCallback((i, di, oi) => ShowOper(i, di, oi) |> dispatch);

  let closeAnimationFull = useCallback(_ => CloseAnimationFull |> dispatch);

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
                      showTab={tabtitem.showTabt}
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
               |> Array.mapi((i, item) =>
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
                                    padding="3"
                                    disabled={state.showProgress}
                                    onClick={event => i |> showOther(event)}>
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
                                  {item.showOther
                                     ? <SelectMenu
                                         top="100%"
                                         right="0"
                                         transform="translate(0, -100%)"
                                         maxWidth="256"
                                         width="256"
                                         maxHeight="280"
                                         minHeight="0"
                                         topLeft="12"
                                         topRight="12"
                                         bottomRight="12"
                                         bottomLeft="12"
                                         paddingRight="8"
                                         paddingLeft="8">
                                         <MenuIcon
                                           top="0"
                                           right="8"
                                           bottom="0"
                                           left="8"
                                           disablePadding=true
                                           topLeft="12"
                                           topRight="12"
                                           bottomRight="12"
                                           bottomLeft="12"
                                           onClick={event =>
                                             i |> exportForm(event, item.id)
                                           }>
                                           ...(
                                                <IconGeneral
                                                  src=doneSuccessful
                                                />,
                                                <FormattedMessage
                                                  id="export"
                                                  defaultMessage="Export"
                                                />,
                                              )
                                         </MenuIcon>
                                       </SelectMenu>
                                     : null}
                                  <BackgroundBoard
                                    showBackground={item.showOther}
                                    backgroundColor="transparent"
                                    onClick={event => i |> showOther(event)}
                                  />
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
    <CircleButton
      style={ReactDOMRe.Style.make(
        ~position="fixed",
        ~right="25px",
        ~bottom="25px",
        (),
      )}
      onClick=showAnimationRight>
      <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
        <FormattedMessage id="Proform.import" defaultMessage="Import" />
      </Tooltip>
      <IconAction animation="leftRight" src=importExportWhite />
    </CircleButton>
    <DialogAnimationRight showAnimation={state.showRight}>
      <DialogTitle
        backgroundColor="rgba(255,0,0,1)" color="rgba(255,255,255,1)">
        <FormattedMessage id="Proform.upload" defaultMessage="Upload" />
      </DialogTitle>
      <DialogContent right="0" bottom="12" left="0">
        <DialogContentText>
          <GridItem top="30" right="25" left="25" xs="12">
            <GeneralUpload
              webLoad={state.showProgress}
              showDrop={state.showDrop}
              fileRef
              onDragOver={event => event |> dragOver}
              onDragLeave={event => event |> dragLeave}
              onDrop={event =>
                ReactEventRe.Synthetic.nativeEvent(event)##dataTransfer##files[0]
                |> dropFile(event)
              }
              disabled={state.showProgress}
              onClick=chooseFile
              onChange={event =>
                ReactEvent.Form.target(event)##files[0] |> uploadFile
              }
            />
          </GridItem>
        </DialogContentText>
      </DialogContent>
      <DialogActions top="0" right="16" bottom="12" left="16">
        <GridContainer
          direction="rowReverse" justify="start" alignItem="center">
          <GridItem top="0" bottom="0" xs="no">
            <Button disabled={state.showProgress} onClick=closeAnimationRight>
              <IconAction animation="circle" src=clearWhite />
              <FormattedMessage id="closed" defaultMessage="Closed" />
            </Button>
          </GridItem>
        </GridContainer>
      </DialogActions>
    </DialogAnimationRight>
    <DialogFull showAnimation={state.showFull}>
      <DialogTitle top="6" left="64"> null </DialogTitle>
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
              <GridItem top="0" right="24" bottom="0" left="24" xs="auto">
                <TextFieldStandard
                  labelColor="rgba(255,0,0,0.8)"
                  enterBorderColor="rgba(255,0,0,0.8)"
                  downBorderColor="rgba(255,0,0,0.6)"
                  borderColor="rgba(0,0,0,0.2)"
                  placeholder="Project Tile"
                  value={state.formTile}
                  disabled={state.showProgress}
                  onChange={event =>
                    ReactEvent.Form.target(event)##value |> changeFormTile
                  }>
                  null
                </TextFieldStandard>
              </GridItem>
              <GridItem top="0" right="24" left="24" xs="auto">
                <TextFieldStandard
                  top="8"
                  labelColor="rgba(255,0,0,0.8)"
                  enterBorderColor="rgba(255,0,0,0.8)"
                  downBorderColor="rgba(255,0,0,0.6)"
                  borderColor="rgba(0,0,0,0.2)"
                  placeholder="Project Desc"
                  value={state.formDesc}
                  disabled={state.showProgress}
                  onChange={event =>
                    ReactEvent.Form.target(event)##value |> changeFormDesc
                  }>
                  null
                </TextFieldStandard>
              </GridItem>
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
                    <Tabs id="report-" index={state.formindex} height="3">
                      {state.formtabitems
                       |> List.mapi((i, formtabitem) =>
                            <Tab
                              showTab={formtabitem.showTab}
                              maxWidth="111.6"
                              borderRadius="15"
                              id={"report-" ++ string_of_int(i)}
                              animationName="none"
                              onClick={_ => i |> clickFormTab}>
                              <IconAction
                                width="28"
                                height="28"
                                animation="leftRight"
                                src={formtabitem.tabImage}
                              />
                            </Tab>
                          )
                       |> Array.of_list
                       |> array}
                    </Tabs>
                  </GridItem>
                  <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                    <Button disabled={state.showProgress} onClick=addForm>
                      <IconAction animation="circle" src=addWhite />
                      <FormattedMessage id="add" defaultMessage="Add" />
                    </Button>
                  </GridItem>
                  <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                    <Button disabled={state.showProgress} onClick=insertForm>
                      <IconAction animation="leftRight" src=saveWhite />
                      <FormattedMessage id="save" defaultMessage="Save" />
                    </Button>
                  </GridItem>
                  <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                    <Button disabled={state.showProgress} onClick=deleteForm>
                      <IconAction animation="leftRight" src=deleteWhite />
                      <FormattedMessage
                        id="deleted"
                        defaultMessage="Deleted"
                      />
                    </Button>
                  </GridItem>
                </GridContainer>
              </GridItem>
              {switch (state.formindex) {
               | 0 =>
                 state.formitems
                 |> Array.mapi((i, formitem) =>
                      <GridItem top="0" right="24" left="24" xs="auto">
                        <CardOrPaperBoard
                          onClick={_ => i |> clickBoardPaper}
                          showLine={formitem.showLine}>
                          <GridContainer
                            direction="column"
                            justify="start"
                            alignItem="stretch">
                            <GridItem top="0" bottom="0" xs="auto">
                              <GridContainer
                                direction="row"
                                justify="center"
                                alignItem="center">
                                <GridItem
                                  top="0"
                                  right="0"
                                  bottom="0"
                                  left="0"
                                  xs="auto">
                                  <TextFieldStandard
                                    top="0"
                                    right="0"
                                    left="0"
                                    value={formitem.title}
                                    disabled={
                                      state.showProgress || formitem.formDelete
                                    }
                                    onChange={event =>
                                      i
                                      |> changeTile(
                                           ReactEvent.Form.target(event)##value,
                                         )
                                    }>
                                    null
                                  </TextFieldStandard>
                                </GridItem>
                                {formitem.showLine
                                   ? <>
                                       <GridItem
                                         top="0"
                                         right="0"
                                         bottom="0"
                                         left="0"
                                         xs="no">
                                         <IconButton
                                           padding="10"
                                           disabled={
                                             state.showProgress
                                             || formitem.formDelete
                                           }>
                                           <IconAction
                                             animation="leftRight"
                                             src=collectionsBlack
                                           />
                                         </IconButton>
                                       </GridItem>
                                       <GridItem
                                         top="0"
                                         right="0"
                                         bottom="0"
                                         left="0"
                                         width="156px"
                                         xs="no">
                                         <SelectOutline
                                           top="0"
                                           borderColor="rgba(0,0,0,0.2)"
                                           value={formitem.outValue}
                                           disabled={
                                             state.showProgress
                                             || formitem.formDelete
                                           }
                                           onClick={_ => i |> showOut}>
                                           ...(
                                                formitem.showOut
                                                && !formitem.formDelete
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
                                                      {formitem.opticonitems
                                                       |> Array.map(
                                                            opticonitem =>
                                                            <MenuIcon
                                                              top="0"
                                                              right="8"
                                                              bottom="0"
                                                              left="8"
                                                              disablePadding={
                                                                    opticonitem.
                                                                    opticonPadding
                                                                    }
                                                              topLeft="12"
                                                              topRight="12"
                                                              bottomRight="12"
                                                              bottomLeft="12"
                                                              onClick={_ =>
                                                                i
                                                                |> showValue(
                                                                    opticonitem.
                                                                    value,
                                                                   )
                                                              }>
                                                              ...(
                                                                   <IconGeneral
                                                                    src={
                                                                    opticonitem.
                                                                    icon
                                                                    }
                                                                   />,
                                                                   opticonitem.
                                                                    value
                                                                   |> string,
                                                                 )
                                                            </MenuIcon>
                                                          )
                                                       |> array}
                                                    </SelectMenu>
                                                  : null,
                                                <IconGeneral
                                                  animation={
                                                    formitem.showOut
                                                    |> topDownRorate
                                                  }
                                                  src=arrowDownBlack
                                                />,
                                              )
                                         </SelectOutline>
                                         <BackgroundBoard
                                           showBackground={formitem.showOut}
                                           backgroundColor="transparent"
                                           onClick={_ => i |> showOut}
                                         />
                                       </GridItem>
                                     </>
                                   : null}
                              </GridContainer>
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
                                   disabled=true
                                 />
                               | "text" =>
                                 <TextFieldStandard
                                   width="50"
                                   top="0"
                                   left="0"
                                   enterBorderColor="rgba(255,0,0,0.8)"
                                   downBorderColor="rgba(255,0,0,0.6)"
                                   borderColor="rgba(0,0,0,0.2)"
                                   disabled=true>
                                   null
                                 </TextFieldStandard>
                               | "textarea" =>
                                 <TextFieldStandard
                                   top="0"
                                   left="0"
                                   enterBorderColor="rgba(255,0,0,0.8)"
                                   downBorderColor="rgba(255,0,0,0.6)"
                                   borderColor="rgba(0,0,0,0.2)"
                                   disabled=true>
                                   null
                                 </TextFieldStandard>
                               | "textline" =>
                                 <TextFieldMultiline
                                   top="12"
                                   bottom="12"
                                   left="0"
                                   labelColor="rgba(255,0,0,0.8)"
                                   borderTop="10"
                                   borderBottom="10"
                                   enterBorderColor="rgba(255,0,0,0.8)"
                                   downBorderColor="rgba(255,0,0,0.6)"
                                   borderColor="rgba(0,0,0,0.2)"
                                   rows=3
                                   disabled=true>
                                   null
                                 </TextFieldMultiline>
                               | "droplist" =>
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
                                                 disabled={state.showProgress}>
                                                 <IconAction
                                                   animation="leftRight"
                                                   src=radioButtonUncheckedBlack
                                                 />
                                               </IconButton>
                                             </GridItem>
                                             <GridItem
                                               top="0"
                                               right="6"
                                               bottom="0"
                                               left="0"
                                               xs="auto">
                                               <TextFieldStandard
                                                 top="0"
                                                 enterBorderColor={
                                                   answeritem.showAnswer
                                                   |> enterBorder
                                                 }
                                                 downBorderColor={
                                                   answeritem.showAnswer
                                                   |> downBorder
                                                 }
                                                 borderColor={
                                                   answeritem.showAnswer
                                                   |> border
                                                 }
                                                 placeholder="Option"
                                                 value={answeritem.value}
                                                 disabled={
                                                   state.showProgress
                                                   || formitem.formDelete
                                                 }
                                                 onChange={event =>
                                                   i
                                                   |> changeText(
                                                        ReactEvent.Form.target(
                                                          event,
                                                        )##value,
                                                        ai,
                                                      )
                                                 }>
                                                 null
                                               </TextFieldStandard>
                                             </GridItem>
                                             {formitem.showLine
                                                ? <GridItem
                                                    top="0"
                                                    right="0"
                                                    bottom="0"
                                                    left="0"
                                                    xs="no">
                                                    <IconButton
                                                      padding="4"
                                                      disabled={
                                                        state.showProgress
                                                        || formitem.formDelete
                                                      }
                                                      onClick={_ =>
                                                        i |> clearOption(ai)
                                                      }>
                                                      <IconAction
                                                        animation="circle"
                                                        src={
                                                          answeritem.ansrDelete
                                                            ? refreshBlack
                                                            : clearWarn
                                                        }
                                                      />
                                                    </IconButton>
                                                  </GridItem>
                                                : null}
                                           </GridContainer>
                                         </GridItem>
                                       )
                                    |> array}
                                 </GridContainer>
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
                                                 disabled={state.showProgress}>
                                                 <IconAction
                                                   animation="leftRight"
                                                   src={
                                                     false
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
                                               <TextFieldStandard
                                                 top="0"
                                                 enterBorderColor={
                                                   answeritem.showAnswer
                                                   |> enterBorder
                                                 }
                                                 downBorderColor={
                                                   answeritem.showAnswer
                                                   |> downBorder
                                                 }
                                                 borderColor={
                                                   answeritem.showAnswer
                                                   |> border
                                                 }
                                                 placeholder="Option"
                                                 value={answeritem.value}
                                                 disabled={
                                                   state.showProgress
                                                   || formitem.formDelete
                                                 }
                                                 onChange={event =>
                                                   i
                                                   |> changeText(
                                                        ReactEvent.Form.target(
                                                          event,
                                                        )##value,
                                                        ai,
                                                      )
                                                 }>
                                                 null
                                               </TextFieldStandard>
                                             </GridItem>
                                             {formitem.showLine
                                                ? <>
                                                    <GridItem
                                                      top="0"
                                                      right="6"
                                                      bottom="0"
                                                      left="0"
                                                      xs="no">
                                                      <IconButton
                                                        padding="4"
                                                        disabled={
                                                          state.showProgress
                                                          || formitem.
                                                               formDelete
                                                        }
                                                        onClick={_ =>
                                                          i
                                                          |> clickElement(
                                                               formitem.
                                                                 outValue,
                                                               ai,
                                                             )
                                                        }>
                                                        <IconAction
                                                          animation="leftRight"
                                                          src={
                                                            answeritem.
                                                              showAnswer
                                                              ? doneSuccessful
                                                              : errorWarn
                                                          }
                                                        />
                                                      </IconButton>
                                                    </GridItem>
                                                    <GridItem
                                                      top="0"
                                                      right="0"
                                                      bottom="0"
                                                      left="0"
                                                      xs="no">
                                                      <IconButton
                                                        padding="4"
                                                        disabled={
                                                          state.showProgress
                                                          || formitem.
                                                               formDelete
                                                        }
                                                        onClick={_ =>
                                                          i |> clearOption(ai)
                                                        }>
                                                        <IconAction
                                                          animation="circle"
                                                          src={
                                                            answeritem.
                                                              ansrDelete
                                                              ? refreshBlack
                                                              : clearWarn
                                                          }
                                                        />
                                                      </IconButton>
                                                    </GridItem>
                                                  </>
                                                : null}
                                           </GridContainer>
                                         </GridItem>
                                       )
                                    |> array}
                                 </GridContainer>
                               }}
                            </GridItem>
                            {formitem.showLine
                               ? <>
                                   {formitem.showVeri
                                      ? <GridItem top="0" bottom="0" xs="auto">
                                          <GridContainer
                                            direction="row"
                                            justify="start"
                                            alignItem="center">
                                            <GridItem
                                              top="0"
                                              right="0"
                                              bottom="0"
                                              left="0"
                                              xs="auto">
                                              <SelectStandard
                                                top="0"
                                                bottom="0"
                                                enterBorderColor="transparent"
                                                downBorderColor="transparent"
                                                borderColor="transparent"
                                                value={formitem.type_}
                                                disabled={
                                                  state.showProgress
                                                  || formitem.formDelete
                                                }
                                                onClick={_ => i |> showType}>
                                                ...(
                                                     formitem.showType
                                                     && !formitem.formDelete
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
                                                           {formitem.typeitems
                                                            |> Array.map(
                                                                 typeitem =>
                                                                 <MenuItem
                                                                   top="0"
                                                                   right="8"
                                                                   bottom="0"
                                                                   left="8"
                                                                   disablePadding={
                                                                    typeitem.
                                                                    optionPadding
                                                                    }
                                                                   topLeft="12"
                                                                   topRight="12"
                                                                   bottomRight="12"
                                                                   bottomLeft="12"
                                                                   onClick={_ =>
                                                                    typeitem.
                                                                    value
                                                                    |>
                                                                    clickType(
                                                                    i,
                                                                    )
                                                                   }>
                                                                   {typeitem.
                                                                    value
                                                                    |> string}
                                                                 </MenuItem>
                                                               )
                                                            |> array}
                                                         </SelectMenu>
                                                       : null,
                                                     <IconGeneral
                                                       animation={
                                                         formitem.showType
                                                         |> topDownRorate
                                                       }
                                                       src=arrowDownBlack
                                                     />,
                                                   )
                                              </SelectStandard>
                                              <BackgroundBoard
                                                showBackground={
                                                                 formitem.
                                                                   showType
                                                               }
                                                backgroundColor="transparent"
                                                onClick={_ => i |> showType}
                                              />
                                            </GridItem>
                                            <GridItem
                                              top="0"
                                              right="0"
                                              bottom="0"
                                              left="0"
                                              xs="auto">
                                              <SelectStandard
                                                top="0"
                                                bottom="0"
                                                enterBorderColor="transparent"
                                                downBorderColor="transparent"
                                                borderColor="transparent"
                                                value={formitem.operation}
                                                disabled={
                                                  state.showProgress
                                                  || formitem.formDelete
                                                }
                                                onClick={_ =>
                                                  i |> showOperation
                                                }>
                                                ...(
                                                     formitem.showOperation
                                                     && !formitem.formDelete
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
                                                           {formitem.
                                                              operationitems
                                                            |> Array.map(
                                                                 operationitem =>
                                                                 <MenuItem
                                                                   top="0"
                                                                   right="8"
                                                                   bottom="0"
                                                                   left="8"
                                                                   disablePadding={
                                                                    operationitem.
                                                                    optionPadding
                                                                    }
                                                                   topLeft="12"
                                                                   topRight="12"
                                                                   bottomRight="12"
                                                                   bottomLeft="12"
                                                                   onClick={_ =>
                                                                    i
                                                                    |>
                                                                    clickOperation(
                                                                    operationitem.
                                                                    value,
                                                                    )
                                                                   }>
                                                                   {operationitem.
                                                                    value
                                                                    |> string}
                                                                 </MenuItem>
                                                               )
                                                            |> array}
                                                         </SelectMenu>
                                                       : null,
                                                     <IconGeneral
                                                       animation={
                                                         formitem.showOperation
                                                         |> topDownRorate
                                                       }
                                                       src=arrowDownBlack
                                                     />,
                                                   )
                                              </SelectStandard>
                                              <BackgroundBoard
                                                showBackground={
                                                                 formitem.
                                                                   showOperation
                                                               }
                                                backgroundColor="transparent"
                                                onClick={_ =>
                                                  i |> showOperation
                                                }
                                              />
                                            </GridItem>
                                            <GridItem
                                              top="0"
                                              right="0"
                                              bottom="0"
                                              left="0"
                                              xs="auto">
                                              <TextFieldStandard
                                                top="0"
                                                right="0"
                                                bottom="0"
                                                left="0"
                                                value={formitem.area}
                                                disabled={
                                                  state.showProgress
                                                  || formitem.formDelete
                                                }
                                                onChange={event =>
                                                  i
                                                  |> changeArea(
                                                       ReactEvent.Form.target(
                                                         event,
                                                       )##value,
                                                     )
                                                }>
                                                null
                                              </TextFieldStandard>
                                            </GridItem>
                                            <GridItem
                                              top="0"
                                              right="0"
                                              bottom="0"
                                              left="0"
                                              xs="auto">
                                              <TextFieldStandard
                                                top="0"
                                                right="0"
                                                bottom="0"
                                                left="0"
                                                value={formitem.eror}
                                                disabled={
                                                  state.showProgress
                                                  || formitem.formDelete
                                                }
                                                onChange={event =>
                                                  i
                                                  |> changeEror(
                                                       ReactEvent.Form.target(
                                                         event,
                                                       )##value,
                                                     )
                                                }>
                                                null
                                              </TextFieldStandard>
                                            </GridItem>
                                            <GridItem
                                              top="0"
                                              right="0"
                                              bottom="0"
                                              left="0"
                                              xs="no">
                                              <IconButton
                                                padding="8"
                                                disabled={
                                                  state.showProgress
                                                  || formitem.formDelete
                                                }
                                                onClick={_ =>
                                                  i |> clearCondition
                                                }>
                                                <IconAction
                                                  animation="circle"
                                                  src=clearBlack
                                                />
                                              </IconButton>
                                            </GridItem>
                                          </GridContainer>
                                        </GridItem>
                                      : null}
                                   <GridItem xs="auto"> <Divider /> </GridItem>
                                   <GridItem
                                     top="0"
                                     right="0"
                                     bottom="0"
                                     left="0"
                                     xs="auto">
                                     <GridContainer
                                       direction="rowReverse"
                                       justify="start"
                                       alignItem="center">
                                       <GridItem
                                         top="0"
                                         right="0"
                                         bottom="0"
                                         left="0"
                                         xs="no">
                                         <IconButton
                                           padding="8"
                                           disabled={
                                             state.showProgress
                                             || formitem.formDelete
                                           }
                                           onClick={_ => i |> showMore}>
                                           <Tooltip
                                             location="top"
                                             backgroundColor="rgba(255,0,0,0.8)">
                                             <FormattedMessage
                                               id="more"
                                               defaultMessage="More"
                                             />
                                           </Tooltip>
                                           <IconAction
                                             animation="circle"
                                             src=moreVertBlack
                                           />
                                         </IconButton>
                                         {formitem.showMore
                                          && !formitem.formDelete
                                            ? <SelectMenu
                                                top="100%"
                                                right="0"
                                                transform="translate(0, -100%)"
                                                maxWidth="256"
                                                width="256"
                                                maxHeight="280"
                                                minHeight="0"
                                                topLeft="12"
                                                topRight="12"
                                                bottomRight="12"
                                                bottomLeft="12"
                                                paddingRight="8"
                                                paddingLeft="8">
                                                {switch (formitem.outValue) {
                                                 | "radio" =>
                                                   <>
                                                     <MenuIcon
                                                       top="0"
                                                       right="8"
                                                       bottom="0"
                                                       left="8"
                                                       disablePadding=true
                                                       topLeft="12"
                                                       topRight="12"
                                                       bottomRight="12"
                                                       bottomLeft="12">
                                                       ...(
                                                            <IconGeneral
                                                              src=doneSuccessful
                                                            />,
                                                            <FormattedMessage
                                                              id="desc"
                                                              defaultMessage="Desc"
                                                            />,
                                                          )
                                                     </MenuIcon>
                                                     <MenuIcon
                                                       top="0"
                                                       right="8"
                                                       bottom="0"
                                                       left="8"
                                                       disablePadding=true
                                                       topLeft="12"
                                                       topRight="12"
                                                       bottomRight="12"
                                                       bottomLeft="12">
                                                       ...(
                                                            <IconGeneral
                                                              src=doneSuccessful
                                                            />,
                                                            <FormattedMessage
                                                              id="Default.relevant"
                                                              defaultMessage="Relevant"
                                                            />,
                                                          )
                                                     </MenuIcon>
                                                   </>
                                                 | "checkbox" =>
                                                   <MenuIcon
                                                     top="0"
                                                     right="8"
                                                     bottom="0"
                                                     left="8"
                                                     disablePadding=true
                                                     topLeft="12"
                                                     topRight="12"
                                                     bottomRight="12"
                                                     bottomLeft="12">
                                                     ...(
                                                          <IconGeneral
                                                            src=doneSuccessful
                                                          />,
                                                          <FormattedMessage
                                                            id="desc"
                                                            defaultMessage="Desc"
                                                          />,
                                                        )
                                                   </MenuIcon>
                                                 | _ =>
                                                   <>
                                                     <MenuIcon
                                                       top="0"
                                                       right="8"
                                                       bottom="0"
                                                       left="8"
                                                       disablePadding=true
                                                       topLeft="12"
                                                       topRight="12"
                                                       bottomRight="12"
                                                       bottomLeft="12">
                                                       ...(
                                                            <IconGeneral
                                                              src=doneSuccessful
                                                            />,
                                                            <FormattedMessage
                                                              id="desc"
                                                              defaultMessage="Desc"
                                                            />,
                                                          )
                                                     </MenuIcon>
                                                     <MenuIcon
                                                       top="0"
                                                       right="8"
                                                       bottom="0"
                                                       left="8"
                                                       disablePadding=true
                                                       topLeft="12"
                                                       topRight="12"
                                                       bottomRight="12"
                                                       bottomLeft="12"
                                                       onClick={_ =>
                                                         i
                                                         |> showVerification(
                                                              formitem.iid,
                                                              formitem.
                                                                showVeri,
                                                            )
                                                       }>
                                                       ...(
                                                            <IconGeneral
                                                              src=doneSuccessful
                                                            />,
                                                            <FormattedMessage
                                                              id="Default.verification"
                                                              defaultMessage="Verification"
                                                            />,
                                                          )
                                                     </MenuIcon>
                                                   </>
                                                 }}
                                              </SelectMenu>
                                            : null}
                                         <BackgroundBoard
                                           showBackground={formitem.showMore}
                                           backgroundColor="transparent"
                                           onClick={_ => i |> showMore}
                                         />
                                       </GridItem>
                                       <GridItem
                                         top="0"
                                         right="0"
                                         bottom="0"
                                         left="0"
                                         xs="no">
                                         <Switch
                                           right="0"
                                           checked={formitem.showCheck}
                                           circleColor={
                                             formitem.showCheck |> circle
                                           }
                                           linearColor={
                                             formitem.showCheck |> linear
                                           }
                                           fontColor={
                                             formitem.showCheck |> font
                                           }
                                           disabled={
                                             state.showProgress
                                             || formitem.formDelete
                                           }
                                           onClick={_ => i |> checkItem}>
                                           <FormattedMessage
                                             id="need"
                                             defaultMessage="Need"
                                           />
                                         </Switch>
                                       </GridItem>
                                       <GridItem
                                         style={ReactDOMRe.Style.make(
                                           ~marginRight="12px",
                                           ~borderRight=
                                             "1px solid rgba(0,0,0,0.12)",
                                           (),
                                         )}
                                         left="0"
                                         xs="no">
                                         null
                                       </GridItem>
                                       <GridItem
                                         top="0"
                                         right="0"
                                         bottom="0"
                                         left="0"
                                         xs="no">
                                         <IconButton
                                           padding="8"
                                           disabled={state.showProgress}
                                           onClick={_ => i |> deleteItem}>
                                           <Tooltip
                                             location="top"
                                             backgroundColor="rgba(255,0,0,0.8)">
                                             <FormattedMessage
                                               id={
                                                 formitem.formDelete
                                                   ? "refresh" : "deleted"
                                               }
                                               defaultMessage={
                                                 formitem.formDelete
                                                   ? "Refresh" : "Deleted"
                                               }
                                             />
                                           </Tooltip>
                                           <IconAction
                                             animation="leftRight"
                                             src={
                                               formitem.formDelete
                                                 ? refreshBlack : deleteBlack
                                             }
                                           />
                                         </IconButton>
                                       </GridItem>
                                       <GridItem
                                         top="0"
                                         right="0"
                                         bottom="0"
                                         left="0"
                                         xs="no">
                                         <IconButton
                                           padding="8"
                                           disabled={
                                             state.showProgress
                                             || formitem.formDelete
                                           }>
                                           <Tooltip
                                             location="top"
                                             backgroundColor="rgba(255,0,0,0.8)">
                                             <FormattedMessage
                                               id="copy"
                                               defaultMessage="Copy"
                                             />
                                           </Tooltip>
                                           <IconAction
                                             animation="leftRight"
                                             src=fileCopyBlack
                                           />
                                         </IconButton>
                                       </GridItem>
                                       {switch (formitem.outValue) {
                                        | "radio"
                                        | "checkbox"
                                        | "droplist" =>
                                          <GridItem
                                            top="0"
                                            right="0"
                                            bottom="0"
                                            left="0"
                                            xs="no">
                                            <IconButton
                                              padding="8"
                                              disabled={
                                                state.showProgress
                                                || formitem.formDelete
                                              }
                                              onClick={_ => i |> addItem}>
                                              <Tooltip
                                                location="top"
                                                backgroundColor="rgba(255,0,0,0.8)">
                                                <FormattedMessage
                                                  id="add"
                                                  defaultMessage="Add"
                                                />
                                              </Tooltip>
                                              <IconAction
                                                animation="circle"
                                                src=addBlack
                                              />
                                            </IconButton>
                                          </GridItem>
                                        | _ => null
                                        }}
                                     </GridContainer>
                                   </GridItem>
                                 </>
                               : null}
                          </GridContainer>
                        </CardOrPaperBoard>
                      </GridItem>
                    )
                 |> array
               | 1 =>
                 state.settitems
                 |> Array.mapi((i, settitem) =>
                      <>
                        <GridItem
                          top="0" right="24" bottom="0" left="24" xs="auto">
                          <GridContainer
                            direction="row"
                            justify="center"
                            alignItem="center">
                            <GridItem
                              top="0" right="0" bottom="0" left="0" xs="auto">
                              <TextFieldOutline
                                top="8"
                                type_="date"
                                value={settitem.stdate}
                                disabled={state.showProgress}
                                onChange={event =>
                                  i
                                  |> changeStdate(
                                       ReactEvent.Form.target(event)##value,
                                     )
                                }>
                                <FormattedMessage
                                  id="Formor.stdate"
                                  defaultMessage="Stdate"
                                />
                              </TextFieldOutline>
                            </GridItem>
                            <GridItem
                              top="0" right="0" bottom="0" left="0" xs="auto">
                              <TextFieldOutline
                                top="8"
                                type_="time"
                                value={settitem.sttime}
                                disabled={state.showProgress}
                                onChange={event =>
                                  i
                                  |> changeSttime(
                                       ReactEvent.Form.target(event)##value,
                                     )
                                }>
                                <FormattedMessage
                                  id="Formor.sttime"
                                  defaultMessage="Sttime"
                                />
                              </TextFieldOutline>
                            </GridItem>
                          </GridContainer>
                        </GridItem>
                        <GridItem
                          top="0" right="24" bottom="0" left="24" xs="auto">
                          <GridContainer
                            direction="row"
                            justify="center"
                            alignItem="center">
                            <GridItem
                              top="0" right="0" bottom="0" left="0" xs="auto">
                              <TextFieldOutline
                                top="8"
                                type_="date"
                                value={settitem.endate}
                                disabled={state.showProgress}
                                onChange={event =>
                                  i
                                  |> changeEndate(
                                       ReactEvent.Form.target(event)##value,
                                     )
                                }>
                                <FormattedMessage
                                  id="Formor.endate"
                                  defaultMessage="Endate"
                                />
                              </TextFieldOutline>
                            </GridItem>
                            <GridItem
                              top="0" right="0" bottom="0" left="0" xs="auto">
                              <TextFieldOutline
                                top="8"
                                type_="time"
                                value={settitem.entime}
                                disabled={state.showProgress}
                                onChange={event =>
                                  i
                                  |> changeEntime(
                                       ReactEvent.Form.target(event)##value,
                                     )
                                }>
                                <FormattedMessage
                                  id="Formor.entime"
                                  defaultMessage="Entme"
                                />
                              </TextFieldOutline>
                            </GridItem>
                          </GridContainer>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="30" xs="auto">
                          <Switch
                            right="0"
                            checked={settitem.showExam}
                            circleColor={settitem.showExam |> circle}
                            linearColor={settitem.showExam |> linear}
                            fontColor={settitem.showExam |> font}
                            disabled={state.showProgress}
                            onClick={_ => i |> showExam}>
                            <FormattedMessage
                              id="Formor.examed"
                              defaultMessage="Examed"
                            />
                          </Switch>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="80" xs="auto">
                          <Switch
                            right="0"
                            checked={settitem.randOption}
                            circleColor={settitem.randOption |> circle}
                            linearColor={settitem.randOption |> linear}
                            fontColor={settitem.randOption |> font}
                            disabled={state.showProgress || !settitem.showExam}
                            onClick={_ => i |> randOption}>
                            <FormattedMessage
                              id="Formor.randopt"
                              defaultMessage="Randopt"
                            />
                          </Switch>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="80" xs="auto">
                          <Switch
                            right="0"
                            checked={settitem.randSubtile}
                            circleColor={settitem.randSubtile |> circle}
                            linearColor={settitem.randSubtile |> linear}
                            fontColor={settitem.randSubtile |> font}
                            disabled={state.showProgress || !settitem.showExam}
                            onClick={_ => i |> randSubtile}>
                            <FormattedMessage
                              id="Formor.randsub"
                              defaultMessage="Randsub"
                            />
                          </Switch>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="80" xs="auto">
                          <Switch
                            right="0"
                            checked={settitem.showRestart}
                            circleColor={settitem.showRestart |> circle}
                            linearColor={settitem.showRestart |> linear}
                            fontColor={settitem.showRestart |> font}
                            disabled={state.showProgress || !settitem.showExam}
                            onClick={_ => i |> showRestart}>
                            <FormattedMessage
                              id="Formor.restart"
                              defaultMessage="Restart"
                            />
                          </Switch>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="80" xs="no">
                          <TextFieldOutline
                            type_="number"
                            value={settitem.number}
                            disabled={state.showProgress || !settitem.showExam}
                            onChange={event =>
                              i
                              |> changeNumber(
                                   ReactEvent.Form.target(event)##value,
                                 )
                            }>
                            <FormattedMessage
                              id="Formor.number"
                              defaultMessage="Number"
                            />
                          </TextFieldOutline>
                        </GridItem>
                      </>
                    )
                 |> array
               | 2 =>
                 state.settitems
                 |> Array.mapi((i, settitem) =>
                      <>
                        <GridItem top="0" right="24" left="24" xs="auto">
                          <Switch
                            right="0"
                            checked={settitem.showLimit}
                            circleColor={settitem.showLimit |> circle}
                            linearColor={settitem.showLimit |> linear}
                            fontColor={settitem.showLimit |> font}
                            disabled={state.showProgress}
                            onClick={_ => i |> showLimit(settitem.showLimit)}>
                            <FormattedMessage
                              id="Formor.limit"
                              defaultMessage="Limit"
                            />
                          </Switch>
                        </GridItem>
                        {settitem.showLimit
                           ? <GridItem
                               style={ReactDOMRe.Style.make(
                                 ~height="2500px",
                                 (),
                               )}
                               top="0"
                               right="24"
                               left="24"
                               bottom="0"
                               xs="auto">
                               {settitem.dertitems
                                |> Array.mapi((di, dertitem) =>
                                     <ExpansionPanel
                                       showPanel={dertitem.showPanel}>
                                       ...(
                                            <ExpansionSummary
                                              showSummary={dertitem.showPanel}
                                              onClick={_ =>
                                                dertitem.operitems
                                                |> showPanel(
                                                     dertitem.dertment,
                                                     i,
                                                     di,
                                                   )
                                              }>
                                              ...(
                                                   <ExpansionBasis>
                                                     <Typography
                                                       variant="subheading"
                                                       color="rgba(0,0,0,0.8)">
                                                       {dertitem.dertment
                                                        |> string}
                                                     </Typography>
                                                   </ExpansionBasis>,
                                                   <IconGeneral
                                                     src={
                                                       dertitem.showPanel
                                                         ? arrowUpBlack
                                                         : arrowDownBlack
                                                     }
                                                   />,
                                                 )
                                            </ExpansionSummary>,
                                            <GridContainer
                                              direction="column"
                                              justify="start"
                                              alignItem="stretch">
                                              {dertitem.operitems
                                               |> Array.mapi((oi, operitem) =>
                                                    <GridItem
                                                      right="0"
                                                      bottom="0"
                                                      left="0"
                                                      xs="auto">
                                                      <GridContainer
                                                        direction="row"
                                                        justify="center"
                                                        alignItem="center">
                                                        <GridItem
                                                          top="0"
                                                          right="0"
                                                          bottom="0"
                                                          left="0"
                                                          xs="auto">
                                                          <Typography
                                                            variant="body1"
                                                            color="rgba(0,0,0,0.8)">
                                                            {operitem.userid
                                                             |> string}
                                                          </Typography>
                                                        </GridItem>
                                                        <GridItem
                                                          top="0"
                                                          right="0"
                                                          bottom="0"
                                                          left="0"
                                                          xs="auto">
                                                          <Typography
                                                            variant="body1"
                                                            color="rgba(0,0,0,0.8)">
                                                            {operitem.name
                                                             |> string}
                                                          </Typography>
                                                        </GridItem>
                                                        <GridItem
                                                          top="0"
                                                          bottom="0"
                                                          xs="no">
                                                          <Switch
                                                            right="0"
                                                            checked={
                                                                    operitem.
                                                                    showOper
                                                                    }
                                                            circleColor={
                                                              operitem.showOper
                                                              |> circle
                                                            }
                                                            linearColor={
                                                              operitem.showOper
                                                              |> linear
                                                            }
                                                            fontColor={
                                                              operitem.showOper
                                                              |> font
                                                            }
                                                            disabled={
                                                                    state.
                                                                    showProgress
                                                                    }
                                                            onClick={_ =>
                                                              oi
                                                              |> showOper(
                                                                   i,
                                                                   di,
                                                                 )
                                                            }>
                                                            <FormattedMessage
                                                              id="add"
                                                              defaultMessage="Add"
                                                            />
                                                          </Switch>
                                                        </GridItem>
                                                      </GridContainer>
                                                    </GridItem>
                                                  )
                                               |> array}
                                            </GridContainer>,
                                          )
                                     </ExpansionPanel>
                                   )
                                |> array}
                             </GridItem>
                           : null}
                      </>
                    )
                 |> array
               | 3 =>
                 state.viewitems
                 |> Array.map(viewitem =>
                      <>
                        <GridItem top="0" right="24" left="24" xs="auto">
                          <GridContainer
                            direction="row"
                            justify="center"
                            alignItem="center">
                            <GridItem
                              top="0" right="0" bottom="0" left="0" xs="auto">
                              <Typography
                                variant="body1" color="rgba(0,0,0,0.8)">
                                {viewitem.vuserid |> string}
                              </Typography>
                            </GridItem>
                            <GridItem
                              top="0" right="0" bottom="0" left="0" xs="auto">
                              <Typography
                                variant="body1" color="rgba(0,0,0,0.8)">
                                {viewitem.vname |> string}
                              </Typography>
                            </GridItem>
                            <GridItem
                              top="0" right="0" bottom="0" left="0" xs="auto">
                              <Typography
                                variant="body1" color="rgba(0,0,0,0.8)">
                                {viewitem.writed |> string}
                              </Typography>
                            </GridItem>
                            <GridItem
                              top="0" right="0" bottom="0" left="0" xs="auto">
                              <Typography
                                variant="body1" color="rgba(0,0,0,0.8)">
                                {viewitem.score |> string}
                              </Typography>
                            </GridItem>
                          </GridContainer>
                        </GridItem>
                      </>
                    )
                 |> array
               | _ => null
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
