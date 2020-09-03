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

type settitem = {
  stdate: string,
  sttime: string,
  endate: string,
  entime: string,
  showExam: bool,
  randOpt: bool,
  randSub: bool,
  showRest: bool,
  showLimt: bool,
  number: string,
};

type answeritem = {
  id: int,
  value: string,
  showAnswer: bool,
  showDelete: bool,
  showModify: bool,
  showCreate: bool,
};

type formitem = {
  iid: int,
  showLine: bool,
  title: string,
  showOut: bool,
  showVer: bool,
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
  itemModify: bool,
  itemCreate: bool,
};

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
  showFull: bool,
  formId: string,
  formTile: string,
  formDesc: string,
  formtabitems: list(tabitem),
  formindex: int,
  formitems: array(formitem),
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
    showVer: false,
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
        showDelete: false,
        showModify: false,
        showCreate: true,
      },
    |],
    itemDelete: false,
    itemModify: false,
    itemCreate: true,
  },
|];

let newansweritem = id => [|
  {
    id,
    value: "",
    showAnswer: false,
    showDelete: false,
    showModify: false,
    showCreate: true,
  },
|];

type action =
  | SettingError
  | SettingFormLoad
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFormPolls(int, array(item))
  | SettingFormItems(int, array(item))
  | SettingSettItems(array(settitem))
  | ClickItemTab(int)
  | ShowAnimationFull(
      string,
      string,
      string,
      array(formitem),
      array(settitem),
    )
  | ChangeTile(string)
  | ChangeDesc(string)
  | ClickFormTab(int)
  | ClickBoardPaper(int)
  | ChangeItemTile(string, int)
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
  | ShowRest(int)
  | ChangeItemNum(string, int)
  | CloseAnimationFull
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
  | SettingSettItems(settitems) => {...state, settitems}
  | ClickItemTab(index) => {
      ...state,
      tabitems:
        List.mapi(
          (i, tabtitem) => {...tabtitem, tabtShow: index == i},
          state.tabitems,
        ),
      index,
    }
  | ShowAnimationFull(id, tile, desc, formitems, settitems) => {
      ...state,
      formId: id,
      formTile: tile,
      formDesc: desc,
      formitems,
      settitems,
      showFull: !state.showFull,
    }
  | ChangeTile(value) => {...state, formTile: value}
  | ChangeDesc(value) => {...state, formDesc: value}
  | ClickFormTab(index) => {
      ...state,
      formtabitems:
        List.mapi(
          (i, tabitem) => {...tabitem, tabShow: index == i},
          state.formtabitems,
        ),
      index,
    }
  | ClickBoardPaper(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, item) => {...item, showLine: index == i},
          state.formitems,
        ),
    }
  | ChangeItemTile(value, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {...formitem, title: value, itemModify: true} : formitem,
          state.formitems,
        ),
    }
  | ShowItemOut(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            {...formitem, showOut: index == i ? !formitem.showOut : false},
          state.formitems,
        ),
    }
  | ShowItemValue(outValue, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {...formitem, outValue, showOut: false, itemModify: true}
              : formitem,
          state.formitems,
        ),
    }
  | ChangeItemText(value, rindex, index) => {
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
                        ? {...answeritem, value, showModify: true}
                        : answeritem,
                    formitem.answeritems,
                  ),
                itemModify: true,
              }
              : formitem,
          state.formitems,
        ),
    }
  | ClickItemRadio(rindex, index) => {
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
                        showModify: true,
                      },
                    formitem.answeritems,
                  ),
                itemModify: true,
              }
              : formitem,
          state.formitems,
        ),
    }
  | ClickItemCheckbox(rindex, index) => {
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
                          showModify: true,
                        }
                        : answeritem,
                    formitem.answeritems,
                  ),
                itemModify: true,
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
                        ? {...answeritem, showDelete: !answeritem.showDelete}
                        : answeritem,
                    formitem.answeritems,
                  ),
                itemModify: true,
              }
              : formitem,
          state.formitems,
        ),
    }
  | ShowItemType(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {...formitem, showType: !formitem.showType} : formitem,
          state.formitems,
        ),
    }
  | ClickItemType(type_, operation, operationitems, index) => {
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
                itemModify: true,
              }
              : formitem,
          state.formitems,
        ),
    }
  | ShowItemOperation(index) => {
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
  | ClickItemOperation(operation, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {
                ...formitem,
                operation,
                showOperation: false,
                itemModify: true,
              }
              : formitem,
          state.formitems,
        ),
    }
  | ChangeItemArea(area, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i ? {...formitem, area, itemModify: true} : formitem,
          state.formitems,
        ),
    }
  | ChangeItemEror(eror, index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i ? {...formitem, eror, itemModify: true} : formitem,
          state.formitems,
        ),
    }
  | ClearItemCondition(index) => {
      ...state,
      formitems:
        Array.mapi(
          (i, formitem) =>
            index == i
              ? {...formitem, showVer: false, showMore: false} : formitem,
          state.formitems,
        ),
    }
  | ShowItemMore(index) => {
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
                showVer: true,
                showMore: false,
                itemModify: true,
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
              ? {...formitem, itemDelete: !formitem.itemDelete} : formitem,
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
                randOpt: settitem.showExam ? false : settitem.randOpt,
                randSub: settitem.showExam ? false : settitem.randSub,
                showRest: settitem.showExam ? false : settitem.showRest,
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
            index == i ? {...settitem, randOpt: !settitem.randOpt} : settitem,
          state.settitems,
        ),
    }
  | RandSubtile(index) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) =>
            index == i ? {...settitem, randSub: !settitem.randSub} : settitem,
          state.settitems,
        ),
    }
  | ShowRest(index) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) =>
            index == i
              ? {...settitem, showRest: !settitem.showRest} : settitem,
          state.settitems,
        ),
    }
  | ChangeItemNum(value, index) => {
      ...state,
      settitems:
        Array.mapi(
          (i, settitem) =>
            index == i ? {...settitem, number: value} : settitem,
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
  showFull: false,
  formId: "",
  formTile: "",
  formDesc: "",
  formtabitems: [
    {tabShow: true, tabImage: questionAnswerBlack},
    {tabShow: false, tabImage: settingsBlack},
    {tabShow: false, tabImage: menuBookBlack},
  ],
  formindex: 0,
  formitems: [||],
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
             //response##data##itemCount |> pollingAJax;
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

  let sItemAJax = id =>
    Js.Promise.(
      dFormData(id, "newid" |> Locals.select)
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

  let changeTile = useCallback(value => ChangeTile(value) |> dispatch);

  let changeDesc = useCallback(value => ChangeDesc(value) |> dispatch);

  let clickFormTab = useCallback(i => ClickFormTab(i) |> dispatch);

  let clickBoardPaper = useCallback(i => ClickBoardPaper(i) |> dispatch);

  let changeItemTile =
    useCallback((value, i) => ChangeItemTile(value, i) |> dispatch);

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
      sRowsData(state.formId, type_, "newid" |> Locals.select)
      |> Axiosapi.Proform.sType
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

  let sveriAJax = (id, i) =>
    Js.Promise.(
      sRowsData(state.formId, id, "newid" |> Locals.select)
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
               ClearItemCondition(i) |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let showVerification =
    useCallback((id, showVer, i) =>
      showVer ? ClearItemCondition(i) |> dispatch : id |> sveriAJax(i)
    );

  let checkItem = useCallback(i => CheckItem(i) |> dispatch);

  let deleteItem = useCallback(i => DeleteItem(i) |> dispatch);

  let addItem = useCallback(i => AddItem(i) |> dispatch);

  let insertAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> uFormData(
           state.formId,
           state.formTile,
           state.formDesc,
           Js_array.filter(
             (formitem: formitem) =>
               formitem.itemDelete === true
               || formitem.itemModify === true
               || formitem.itemCreate === true,
             state.formitems,
           ),
           state.settitems,
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
      dFormData(state.formId, "newid" |> Locals.select)
      |> Axiosapi.Proform.delete
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
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

  let showRest = useCallback(i => ShowRest(i) |> dispatch);

  let changeItemNum =
    useCallback((value, i) => ChangeItemNum(value, i) |> dispatch);

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
    <DialogFull showAnimation={state.showFull}>
      <DialogTitle top="6" left="64">
        <TextFieldStandard
          width="25"
          top="0"
          right="0"
          bottom="0"
          left="0"
          value={state.formTile}
          disabled={state.showProgress}
          onChange={event =>
            ReactEvent.Form.target(event)##value |> changeTile
          }>
          null
        </TextFieldStandard>
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
                      {state.formtabitems
                       |> List.mapi((i, formtabitem) =>
                            <Tab
                              tabShow={formtabitem.tabShow}
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
                    <Button onClick=addForm>
                      <IconAction animation="circle" src=addWhite />
                      <FormattedMessage id="add" defaultMessage="Add" />
                    </Button>
                  </GridItem>
                  <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                    <Button onClick=insertForm>
                      <IconAction animation="leftRight" src=saveWhite />
                      <FormattedMessage id="save" defaultMessage="Save" />
                    </Button>
                  </GridItem>
                  <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                    <Button onClick=deleteForm>
                      <IconAction animation="leftRight" src=deleteWhite />
                      <FormattedMessage
                        id="deleted"
                        defaultMessage="Deleted"
                      />
                    </Button>
                  </GridItem>
                </GridContainer>
              </GridItem>
              {switch (state.index) {
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
                                      state.showProgress || formitem.itemDelete
                                    }
                                    onChange={event =>
                                      i
                                      |> changeItemTile(
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
                                             || formitem.itemDelete
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
                                             || formitem.itemDelete
                                           }
                                           onClick={_ => i |> showItemOut}>
                                           ...(
                                                formitem.showOut
                                                && !formitem.itemDelete
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
                                           onClick={_ => i |> showItemOut}
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
                               | _ =>
                                 formitem.answeritems
                                 |> Array.mapi((ri, answeritem) =>
                                      <QuestionForm
                                        startIcon={
                                          switch (formitem.outValue) {
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
                                          state.showProgress
                                          || formitem.itemDelete
                                        }
                                        showLine={formitem.showLine}
                                        clickCenter={_ =>
                                          i
                                          |> clickElement(
                                               formitem.outValue,
                                               ri,
                                             )
                                        }
                                        centerIcon={
                                          answeritem.showAnswer
                                            ? doneSuccessful : errorWarn
                                        }
                                        clickEnd={_ => i |> clearOption(ri)}
                                        endIcon={
                                          answeritem.showDelete
                                            ? refreshBlack : clearWarn
                                        }
                                      />
                                    )
                                 |> array
                               }}
                            </GridItem>
                            {formitem.showLine
                               ? <>
                                   {formitem.showVer
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
                                                  || formitem.itemDelete
                                                }
                                                onClick={_ =>
                                                  i |> showItemType
                                                }>
                                                ...(
                                                     formitem.showType
                                                     && !formitem.itemDelete
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
                                                                    clickItemType(
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
                                                onClick={_ =>
                                                  i |> showItemType
                                                }
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
                                                  || formitem.itemDelete
                                                }
                                                onClick={_ =>
                                                  i |> showItemOperation
                                                }>
                                                ...(
                                                     formitem.showOperation
                                                     && !formitem.itemDelete
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
                                                                    clickItemOperation(
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
                                                value={formitem.area}
                                                disabled={
                                                  state.showProgress
                                                  || formitem.itemDelete
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
                                                value={formitem.eror}
                                                disabled={
                                                  state.showProgress
                                                  || formitem.itemDelete
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
                                                  || formitem.itemDelete
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
                                             state.showProgress
                                             || formitem.itemDelete
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
                                         {formitem.showMore
                                          && !formitem.itemDelete
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
                                                              formitem.showVer,
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
                                             || formitem.itemDelete
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
                                                 formitem.itemDelete
                                                   ? "refresh" : "deleted"
                                               }
                                               defaultMessage={
                                                 formitem.itemDelete
                                                   ? "Refresh" : "Deleted"
                                               }
                                             />
                                           </Tooltip>
                                           <IconAction
                                             animation="leftRight"
                                             src={
                                               formitem.itemDelete
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
                                             || formitem.itemDelete
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
                                                || formitem.itemDelete
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
                            checked={settitem.randOpt}
                            circleColor={settitem.randOpt |> circle}
                            linearColor={settitem.randOpt |> linear}
                            fontColor={settitem.randOpt |> font}
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
                            checked={settitem.randSub}
                            circleColor={settitem.randSub |> circle}
                            linearColor={settitem.randSub |> linear}
                            fontColor={settitem.randSub |> font}
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
                            checked={settitem.showRest}
                            circleColor={settitem.showRest |> circle}
                            linearColor={settitem.showRest |> linear}
                            fontColor={settitem.showRest |> font}
                            disabled={state.showProgress || !settitem.showExam}
                            onClick={_ => i |> showRest}>
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
                              |> changeItemNum(
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
