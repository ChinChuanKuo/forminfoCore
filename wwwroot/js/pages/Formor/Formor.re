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

type answeritem = {
  id: int,
  value: string,
  showAnswer: bool,
  ansrDelete: bool,
};

type item = {
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
  itemDelete: bool,
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
  tile: string,
  desc: string,
  tabitems: list(tabitem),
  index: int,
  items: array(item),
  settitems: array(settitem),
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
      {id: 1, value: "", showAnswer: false, ansrDelete: false},
    |],
    itemDelete: false,
  },
|];

let newansweritem = id => [|
  {id, value: "", showAnswer: false, ansrDelete: false},
|];

type action =
  | SettingError
  | SettingFormLoad
  | SettingFormWidth(int, int)
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFormItems(array(item), array(settitem))
  | ChangeTile(string)
  | ChangeDesc(string)
  | ClickItemTab(int)
  | ClickBoardPaper(int)
  | ChangeItemTitle(string, int)
  | ShowItemOut(int)
  | ShowItemValue(string, int)
  | ChangeItemText(string, int, int)
  | ClickItemRadio(int, int)
  | ClickItemCheckbox(int, int)
  | ClearOption(int, int)
  | ShowItemType(int)
  | ClickItemType(string, string, array(optionitem), int)
  | ShowItemOperation(int)
  | ClickItemOperation(string, int)
  | ChangeItemArea(string, int)
  | ChangeItemEror(string, int)
  | ClearItemCondition(int)
  | ShowItemMore(int)
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
  | SettingFormItems(items, settitems) => {...state, items, settitems}
  | ChangeTile(value) => {...state, tile: value}
  | ChangeDesc(value) => {...state, desc: value}
  | ClickItemTab(index) => {
      ...state,
      tabitems:
        List.mapi(
          (i, tabitem) => {...tabitem, tabShow: index == i},
          state.tabitems,
        ),
      index,
    }
  | ClickBoardPaper(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => {...item, showLine: index == i},
          state.items,
        ),
    }
  | ChangeItemTitle(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, title: value} : item,
          state.items,
        ),
    }
  | ShowItemOut(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            {...item, showOut: index == i ? !item.showOut : false},
          state.items,
        ),
    }
  | ShowItemValue(outValue, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, outValue, showOut: false} : item,
          state.items,
        ),
    }
  | ChangeItemText(value, rindex, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                answeritems:
                  Array.mapi(
                    (ri, answeritem) =>
                      rindex == ri ? {...answeritem, value} : answeritem,
                    item.answeritems,
                  ),
              }
              : item,
          state.items,
        ),
    }
  | ClickItemRadio(rindex, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                answeritems:
                  Array.mapi(
                    (ri, answeritem) =>
                      {
                        ...answeritem,
                        showAnswer:
                          rindex == ri ? !answeritem.showAnswer : false,
                      },
                    item.answeritems,
                  ),
              }
              : item,
          state.items,
        ),
    }
  | ClickItemCheckbox(rindex, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                answeritems:
                  Array.mapi(
                    (ri, answeritem) =>
                      rindex == ri
                        ? {...answeritem, showAnswer: !answeritem.showAnswer}
                        : answeritem,
                    item.answeritems,
                  ),
              }
              : item,
          state.items,
        ),
    }
  | ClearOption(rindex, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                answeritems:
                  Array.mapi(
                    (ri, answeritem) =>
                      rindex == ri
                        ? {...answeritem, ansrDelete: !answeritem.ansrDelete}
                        : answeritem,
                    item.answeritems,
                  ),
              }
              : item,
          state.items,
        ),
    }
  | ShowItemType(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showType: !item.showType} : item,
          state.items,
        ),
    }
  | ClickItemType(type_, operation, operationitems, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, type_, operation, operationitems, showType: false}
              : item,
          state.items,
        ),
    }
  | ShowItemOperation(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showOperation: !item.showOperation} : item,
          state.items,
        ),
    }
  | ClickItemOperation(operation, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, operation, showOperation: false} : item,
          state.items,
        ),
    }
  | ChangeItemArea(area, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, area} : item,
          state.items,
        ),
    }
  | ChangeItemEror(eror, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, eror} : item,
          state.items,
        ),
    }
  | ClearItemCondition(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showVeri: false, showMore: false} : item,
          state.items,
        ),
    }
  | ShowItemMore(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showMore: !item.showMore} : item,
          state.items,
        ),
    }
  | ShowItemVerification(type_, typeitems, operation, operationitems, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                type_,
                typeitems,
                operation,
                operationitems,
                showVeri: true,
                showMore: false,
              }
              : item,
          state.items,
        ),
    }
  | CheckItem(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showCheck: !item.showCheck} : item,
          state.items,
        ),
    }
  | DeleteItem(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, itemDelete: !item.itemDelete} : item,
          state.items,
        ),
    }
  | AddItem(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                answeritems:
                  Array.append(
                    item.answeritems,
                    newansweritem(
                      state.items[i].answeritems[Js_array.length(
                                                   item.answeritems,
                                                 )
                                                 - 1].
                        id
                      + 1,
                    ),
                  ),
              }
              : item,
          state.items,
        ),
    }
  | AddForm(opticonitems) => {
      ...state,
      items:
        Array.append(
          state.items,
          newitem(
            state.items[Js_array.length(state.items) - 1].iid + 1,
            opticonitems,
          ),
        ),
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
  tile: "noTitle",
  desc: "",
  tabitems: [
    {tabShow: true, tabImage: questionAnswerBlack},
    {tabShow: false, tabImage: settingsBlack},
    {tabShow: false, tabImage: personAddBlack},
  ],
  index: 0,
  items: [||],
  settitems: [||],
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

  let searchAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Axiosapi.Formor.search
      |> then_(response =>
           {
             SettingFormItems(response##data##items, response##data##settitems)
             |> dispatch;
             ActionShowProgress |> dispatch;
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

  let changeTile = useCallback(value => ChangeTile(value) |> dispatch);

  let changeDesc = useCallback(value => ChangeDesc(value) |> dispatch);

  let clickItemTab = useCallback(i => ClickItemTab(i) |> dispatch);

  let clickBoardPaper = useCallback(i => ClickBoardPaper(i) |> dispatch);

  let changeItemTitle =
    useCallback((value, i) => ChangeItemTitle(value, i) |> dispatch);

  let showItemOut = useCallback(i => ShowItemOut(i) |> dispatch);

  let showItemValue =
    useCallback((value, i) => ShowItemValue(value, i) |> dispatch);

  let changeItemText =
    useCallback((value, ri, i) => ChangeItemText(value, ri, i) |> dispatch);

  let clickElement =
    useCallback((value, ri, i) =>
      switch (value) {
      | "checkbox" => ClickItemCheckbox(ri, i) |> dispatch
      | _ => ClickItemRadio(ri, i) |> dispatch
      }
    );

  let clearOption = useCallback((ri, i) => ClearOption(ri, i) |> dispatch);

  let showItemType = useCallback(i => ShowItemType(i) |> dispatch);

  let stypeAJax = (type_, i) =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> otherData(type_)
      |> Axiosapi.Formor.sType
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ClickItemType(
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
               ClearItemCondition(i) |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickItemType = useCallback((type_, i) => type_ |> stypeAJax(i));

  let showItemOperation = useCallback(i => ShowItemOperation(i) |> dispatch);

  let clickItemOperation =
    useCallback((operation, i) =>
      ClickItemOperation(operation, i) |> dispatch
    );

  let changeItemArea =
    useCallback((area, i) => ChangeItemArea(area, i) |> dispatch);

  let changeItemEror =
    useCallback((area, i) => ChangeItemEror(area, i) |> dispatch);

  let clearItemCondition =
    useCallback(i => ClearItemCondition(i) |> dispatch);

  let showItemMore = useCallback(i => ShowItemMore(i) |> dispatch);

  let sveriAJax = i =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Axiosapi.Formor.sVeri
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
               ClearItemCondition(i) |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let showVerification =
    useCallback((showVeri, i) =>
      showVeri ? ClearItemCondition(i) |> dispatch : i |> sveriAJax
    );

  let checkItem = useCallback(i => CheckItem(i) |> dispatch);

  let deleteItem = useCallback(i => DeleteItem(i) |> dispatch);

  let addItem = useCallback(i => AddItem(i) |> dispatch);

  let insertAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> iFormsData(
           state.tile,
           state.desc,
           Js_array.filter(
             (item: item) => item.itemDelete !== true,
             state.items,
           ),
           state.settitems,
           Js_array.filter(
             (dertitem: dertitem) => dertitem.dertModify === true,
             state.settitems[0].dertitems,
           ),
         )
      |> Axiosapi.Formor.insert
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" => proformPath |> ReasonReactRouter.push
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
      |> Axiosapi.Formor.add
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

  let sLimitAJax = i =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Axiosapi.Formor.sLimit
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
      value
      |> otherData("newid" |> Locals.select)
      |> Axiosapi.Formor.sOper
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

  <>
    <NewFacetube showProgress={state.showProgress} error={state.error}>
      <GridItem
        style=marginAuto
        top="0"
        right="0"
        bottom="0"
        left="54"
        xs="12"
        maxWidth="770px">
        <GridContainer direction="column" justify="center" alignItem="stretch">
          <GridItem top="0" right="24" bottom="0" left="24" xs="auto">
            <TextFieldStandard
              labelColor="rgba(255,0,0,0.8)"
              enterBorderColor="rgba(255,0,0,0.8)"
              downBorderColor="rgba(255,0,0,0.6)"
              borderColor="rgba(0,0,0,0.2)"
              placeholder="Project Tile"
              value={state.tile}
              disabled={state.showProgress}
              onChange={event =>
                ReactEvent.Form.target(event)##value |> changeTile
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
              value={state.desc}
              disabled={state.showProgress}
              onChange={event =>
                ReactEvent.Form.target(event)##value |> changeDesc
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
            <GridContainer direction="row" justify="around" alignItem="center">
              <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                <Tabs id="report-" index={state.index} height="3">
                  {state.tabitems
                   |> List.mapi((i, tabitem) =>
                        <Tab
                          tabShow={tabitem.tabShow}
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
            </GridContainer>
          </GridItem>
          {switch (state.index) {
           | 0 =>
             state.items
             |> Array.mapi((i, item) =>
                  <GridItem top="0" right="24" left="24" xs="auto">
                    <CardOrPaperBoard
                      onClick={_ => i |> clickBoardPaper}
                      showLine={item.showLine}>
                      <GridContainer
                        direction="column" justify="start" alignItem="stretch">
                        <GridItem top="0" bottom="0" xs="auto">
                          <GridContainer
                            direction="row"
                            justify="center"
                            alignItem="center">
                            <GridItem
                              top="0" right="0" bottom="0" left="0" xs="auto">
                              <TextFieldStandard
                                top="0"
                                right="0"
                                left="0"
                                value={item.title}
                                disabled={
                                  state.showProgress || item.itemDelete
                                }
                                onChange={event =>
                                  i
                                  |> changeItemTitle(
                                       ReactEvent.Form.target(event)##value,
                                     )
                                }>
                                null
                              </TextFieldStandard>
                            </GridItem>
                            {item.showLine
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
                                         state.showProgress || item.itemDelete
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
                                       value={item.outValue}
                                       disabled={
                                         state.showProgress || item.itemDelete
                                       }
                                       onClick={_ => i |> showItemOut}>
                                       ...(
                                            item.showOut && !item.itemDelete
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
                                                  {item.opticonitems
                                                   |> Array.map(opticonitem =>
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
                                                            |> showItemValue(
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
                                                item.showOut |> topDownRorate
                                              }
                                              src=arrowDownBlack
                                            />,
                                          )
                                     </SelectOutline>
                                     <BackgroundBoard
                                       showBackground={item.showOut}
                                       backgroundColor="transparent"
                                       onClick={_ => i |> showItemOut}
                                     />
                                   </GridItem>
                                 </>
                               : null}
                          </GridContainer>
                        </GridItem>
                        <GridItem top="0" bottom="0" xs="auto">
                          {switch (item.outValue) {
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
                               showDrop={item.showDrop}
                               showFile={item.showFile}
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
                           | _ =>
                             item.answeritems
                             |> Array.mapi((ri, answeritem) =>
                                  <QuestionForm
                                    startIcon={
                                      switch (item.outValue) {
                                      | "radio" => radioButtonCheckedBlack
                                      | "checkbox" => checkBoxBlack
                                      | _ => checkBoxBlack
                                      }
                                    }
                                    onChange={event =>
                                      i
                                      |> changeItemText(
                                           ReactEvent.Form.target(event)##value,
                                           ri,
                                         )
                                    }
                                    enterBorderColor={
                                      answeritem.showAnswer |> enterBorder
                                    }
                                    downBorderColor={
                                      answeritem.showAnswer |> downBorder
                                    }
                                    borderColor={
                                      answeritem.showAnswer |> border
                                    }
                                    value={answeritem.value}
                                    disabled={
                                      state.showProgress || item.itemDelete
                                    }
                                    showLine={item.showLine}
                                    clickCenter={_ =>
                                      i |> clickElement(item.outValue, ri)
                                    }
                                    centerIcon={
                                      answeritem.showAnswer
                                        ? doneSuccessful : errorWarn
                                    }
                                    clickEnd={_ => i |> clearOption(ri)}
                                    endIcon={
                                      answeritem.ansrDelete
                                        ? refreshBlack : clearWarn
                                    }
                                  />
                                )
                             |> array
                           }}
                        </GridItem>
                        {item.showLine
                           ? <>
                               {item.showVeri
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
                                            value={item.type_}
                                            disabled={
                                              state.showProgress
                                              || item.itemDelete
                                            }
                                            onClick={_ => i |> showItemType}>
                                            ...(
                                                 item.showType
                                                 && !item.itemDelete
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
                                                       {item.typeitems
                                                        |> Array.map(typeitem =>
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
                                                                 typeitem.value
                                                                 |> clickItemType(
                                                                    i,
                                                                    )
                                                               }>
                                                               {typeitem.value
                                                                |> string}
                                                             </MenuItem>
                                                           )
                                                        |> array}
                                                     </SelectMenu>
                                                   : null,
                                                 <IconGeneral
                                                   animation={
                                                     item.showType
                                                     |> topDownRorate
                                                   }
                                                   src=arrowDownBlack
                                                 />,
                                               )
                                          </SelectStandard>
                                          <BackgroundBoard
                                            showBackground={item.showType}
                                            backgroundColor="transparent"
                                            onClick={_ => i |> showItemType}
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
                                            value={item.operation}
                                            disabled={
                                              state.showProgress
                                              || item.itemDelete
                                            }
                                            onClick={_ =>
                                              i |> showItemOperation
                                            }>
                                            ...(
                                                 item.showOperation
                                                 && !item.itemDelete
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
                                                       {item.operationitems
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
                                                                 |> clickItemOperation(
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
                                                     item.showOperation
                                                     |> topDownRorate
                                                   }
                                                   src=arrowDownBlack
                                                 />,
                                               )
                                          </SelectStandard>
                                          <BackgroundBoard
                                            showBackground={item.showOperation}
                                            backgroundColor="transparent"
                                            onClick={_ =>
                                              i |> showItemOperation
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
                                            value={item.area}
                                            disabled={
                                              state.showProgress
                                              || item.itemDelete
                                            }
                                            onChange={event =>
                                              i
                                              |> changeItemArea(
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
                                            value={item.eror}
                                            disabled={
                                              state.showProgress
                                              || item.itemDelete
                                            }
                                            onChange={event =>
                                              i
                                              |> changeItemEror(
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
                                              || item.itemDelete
                                            }
                                            onClick={_ =>
                                              i |> clearItemCondition
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
                                         state.showProgress || item.itemDelete
                                       }
                                       onClick={_ => i |> showItemMore}>
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
                                     {item.showMore && !item.itemDelete
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
                                            {switch (item.outValue) {
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
                                                          id="Formor.relevant"
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
                                                          item.showVeri,
                                                        )
                                                   }>
                                                   ...(
                                                        <IconGeneral
                                                          src=doneSuccessful
                                                        />,
                                                        <FormattedMessage
                                                          id="Formor.verification"
                                                          defaultMessage="Verification"
                                                        />,
                                                      )
                                                 </MenuIcon>
                                               </>
                                             }}
                                          </SelectMenu>
                                        : null}
                                     <BackgroundBoard
                                       showBackground={item.showMore}
                                       backgroundColor="transparent"
                                       onClick={_ => i |> showItemMore}
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
                                       checked={item.showCheck}
                                       circleColor={item.showCheck |> circle}
                                       linearColor={item.showCheck |> linear}
                                       fontColor={item.showCheck |> font}
                                       disabled={
                                         state.showProgress || item.itemDelete
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
                                             item.itemDelete
                                               ? "refresh" : "deleted"
                                           }
                                           defaultMessage={
                                             item.itemDelete
                                               ? "Refresh" : "Deleted"
                                           }
                                         />
                                       </Tooltip>
                                       <IconAction
                                         animation="leftRight"
                                         src={
                                           item.itemDelete
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
                                         state.showProgress || item.itemDelete
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
                                   {switch (item.outValue) {
                                    | "radio"
                                    | "checkbox" =>
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
                                            || item.itemDelete
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
                        direction="row" justify="center" alignItem="center">
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
                        direction="row" justify="center" alignItem="center">
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
                    <GridItem top="0" right="0" bottom="0" left="30" xs="auto">
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
                    <GridItem top="0" right="0" bottom="0" left="80" xs="auto">
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
                    <GridItem top="0" right="0" bottom="0" left="80" xs="auto">
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
                    <GridItem top="0" right="0" bottom="0" left="80" xs="auto">
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
                    <GridItem top="0" right="0" bottom="0" left="80" xs="no">
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
           | _ =>
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
                           style={ReactDOMRe.Style.make(~height="2500px", ())}
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
                                                   {dertitem.dertment |> string}
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
                                                          |> showOper(i, di)
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
           }}
        </GridContainer>
      </GridItem>
    </NewFacetube>
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {state.youtubeText |> string} </span>, null)
    </SnackbarYoutube>
  </>;
};
