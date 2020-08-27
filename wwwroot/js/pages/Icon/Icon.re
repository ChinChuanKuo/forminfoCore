open React;
open Data;
open Items;
open Together;
open Storage;
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

type item = {
  icon: string,
  value: string,
};

type state = {
  formLoad: bool,
  showProgress: bool,
  error: bool,
  items: array(item),
  qaitems: array(item),
  tabitems: list(tabitem),
  index: int,
  bottomitems: list(bottomitem),
  showYoutube: bool,
  youtubeText: string,
};

type action =
  | SettingError
  | SettingFormLoad
  | ActionShowProgress
  | ClickItemTab(int)
  | ClickBottomNavigation(int)
  | ActionSnackBar(string, bool);

let reducer = (state, action) =>
  switch (action) {
  | SettingError => {...state, error: !state.error}
  | SettingFormLoad => {...state, formLoad: !state.formLoad}
  | ActionShowProgress => {...state, showProgress: !state.showProgress}
  | ClickItemTab(index) => {
      ...state,
      tabitems:
        List.mapi(
          (i, tabitem) => {...tabitem, tabShow: index == i},
          state.tabitems,
        ),
      index,
    }
  | ClickBottomNavigation(index) => {
      ...state,
      bottomitems:
        List.mapi(
          (i, item) => {...item, actionShow: index == i},
          state.bottomitems,
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
  showProgress: true,
  error: false,
  items: [|
    {icon: Icons.addBlack, value: "add"},
    {icon: Icons.arrowUpBlack, value: "arrowUp"},
    {icon: Icons.assistantBlack, value: "assistant"},
    {icon: Icons.arrowDownBlack, value: "arrowDown"},
    {icon: Icons.attachFileBlack, value: "attachFile"},
    {icon: Icons.accesstimeBlack, value: "accesstime"},
    {icon: Icons.accountBoxBlack, value: "accountBox"},
    {icon: Icons.accountTreeBlack, value: "accountTree"},
    {icon: Icons.announcementBlack, value: "announcement"},
    {icon: Icons.arrowBackIosBlack, value: "arrowBackIos"},
    {icon: Icons.assignmentIndBlack, value: "assignmentInd"},
    {icon: Icons.arrowForwardIosBlack, value: "arrowForwardIos"},
    {icon: Icons.barChartBlack, value: "barChart"},
    {icon: Icons.brightness4Black, value: "brightness4"},
    {icon: Icons.brightnessLowBlack, value: "brightnessLow"},
    {icon: Icons.brightnessHighBlack, value: "brightnessHigh"},
    {icon: Icons.cancelBlack, value: "cancel"},
    {icon: Icons.clearBlack, value: "clear"},
    {icon: Icons.createBlack, value: "create"},
    {icon: Icons.checkBoxBlack, value: "checkBox"},
    {icon: Icons.colorLensBlack, value: "colorLens"},
    {icon: Icons.cardTravelBlack, value: "cardTravel"},
    {icon: Icons.chatBubbleBlack, value: "chatBubble"},
    {icon: Icons.collectionsBlack, value: "collections"},
    {icon: Icons.cloudDownloadBlack, value: "cloudDownload"},
    {icon: Icons.doneBlack, value: "done"},
    {icon: Icons.deleteBlack, value: "delete"},
    {icon: Icons.dateRangeBlack, value: "dateRange"},
    {icon: Icons.descriptionBlack, value: "description"},
    {icon: Icons.editBlack, value: "edit"},
    {icon: Icons.emailBlack, value: "email"},
    {icon: Icons.eventBlack, value: "event"},
    {icon: Icons.errorBlack, value: "error"},
    {icon: Icons.flagBlack, value: "flag"},
    {icon: Icons.fileCopyBlack, value: "fileCopy"},
    {icon: Icons.formatBoldBlack, value: "formatBold"},
    {icon: Icons.formatSizeBlack, value: "formatSize"},
    {icon: Icons.formatClearBlack, value: "formatClear"},
    {icon: Icons.formatItalicBlack, value: "formatItalic"},
    {icon: Icons.formatUnderlinedBlack, value: "formatUnderlined"},
    {icon: Icons.formatAlignLeftBlack, value: "formatAlignLeft"},
    {icon: Icons.formatAlignRightBlack, value: "formatAlignRight"},
    {icon: Icons.formatAlignCenterBlack, value: "formatAlignCenter"},
    {icon: Icons.formatListBulletedBlack, value: "formatListBulleted"},
    {icon: Icons.formatListNumberedBlack, value: "formatListNumbered"},
    {icon: Icons.formatIndentDecreaseBlack, value: "formatIndentDecrease"},
    {icon: Icons.formatIndentIncreaseBlack, value: "formatIndentIncrease"},
    {icon: Icons.groupBlack, value: "group"},
    {icon: Icons.homeBlack, value: "home"},
    {icon: Icons.helpBlack, value: "help"},
    {icon: Icons.helpOutlineBlack, value: "helpOutline"},
    {icon: Icons.imageBlack, value: "image"},
    {icon: Icons.inputBlack, value: "input"},
    {icon: Icons.importContactsBlack, value: "importContacts"},
    {icon: Icons.insertInvitationBlack, value: "insertInvitation"},
    {icon: Icons.keyboardBlack, value: "keyboardBlack"},
    {icon: Icons.keyboardBackspaceBlack, value: "keyboardBackspace"},
    {icon: Icons.keyboardArrowRightBlack, value: "keyboardArrowRight"},
    {icon: Icons.lockBlack, value: "lock"},
    {icon: Icons.languageBlack, value: "language"},
    {icon: Icons.libraryBooksBlack, value: "libraryBooks"},
    {icon: Icons.localActivityBlack, value: "localActivity"},
    {icon: Icons.mapBlack, value: "map"},
    {icon: Icons.mailBlack, value: "mail"},
    {icon: Icons.menuBlack, value: "menu"},
    {icon: Icons.menuBookBlack, value: "menuBook"},
    {icon: Icons.moreVertBlack, value: "moreVert"},
    {icon: Icons.monetizationOnBlack, value: "monetizationOn"},
    {icon: Icons.notesBlack, value: "notes"},
    {icon: Icons.nightsStayBlack, value: "nightsStay"},
    {icon: Icons.notificationsBlack, value: "notifications"},
    {icon: Icons.notificationsActiveBlack, value: "notificationsActive"},
    {icon: Icons.notificationImportantBlack, value: "notificationImportant"},
    {icon: Icons.photoBlack, value: "photo"},
    {icon: Icons.personBlack, value: "person"},
    {icon: Icons.peopleBlack, value: "people"},
    {icon: Icons.personAddBlack, value: "personAdd"},
    {icon: Icons.privacyTipBlack, value: "privacyTip"},
    {icon: Icons.questionAnswerBlack, value: "questionAnswer"},
    {icon: Icons.restoreBlack, value: "restore"},
    {icon: Icons.refreshBlack, value: "refresh"},
    {icon: Icons.radioButtonCheckedBlack, value: "radioButtonChecked"},
    {icon: Icons.sendBlack, value: "send"},
    {icon: Icons.saveBlack, value: "save"},
    {icon: Icons.storeBlack, value: "store"},
    {icon: Icons.shareBlack, value: "share"},
    {icon: Icons.searchBlack, value: "search"},
    {icon: Icons.settingsBlack, value: "settings"},
    {icon: Icons.storefrontBlack, value: "storefront"},
    {icon: Icons.securityBlack, value: "security"},
    {icon: Icons.shortTextBlack, value: "shortText"},
    {icon: Icons.strikethroughSBlack, value: "strikethroughS"},
    {icon: Icons.settingsApplicationsBlack, value: "settingsApplications"},
    {icon: Icons.todayBlack, value: "today"},
    {icon: Icons.translateBlack, value: "translate"},
    {icon: Icons.textFormatBlack, value: "textFormat"},
    {icon: Icons.textFieldsBlack, value: "textFields"},
    {icon: Icons.wifiBlack, value: "wifi"},
    {icon: Icons.wifiOffBlack, value: "wifiOff"},
  |],
  qaitems: [|
    {icon: Icons.shortTextBlack, value: "text"},
    {icon: Icons.radioButtonCheckedBlack, value: "radio"},
    {icon: Icons.checkBoxBlack, value: "checkbox"},
    {icon: Icons.notesBlack, value: "textarea"},
    {icon: Icons.imageBlack, value: "image"},
    {icon: Icons.collectionsBlack, value: "collections"},
  |],
  tabitems: [
    {tabShow: true, tabImage: Icons.homeBlack},
    {tabShow: false, tabImage: Icons.homeBlack},
  ],
  index: 0,
  bottomitems: [
    {
      actionShow: true,
      icon: Icons.settingsApplicationsBlack,
      tile: "Settings",
    },
    {actionShow: true, icon: Icons.saveBlack, tile: "Save"},
  ],
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
      |> Axiosapi.Icon.search
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" => ActionShowProgress |> dispatch
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

  useEffect(() =>
    if (state.formLoad) {
      Some(() => "action" |> Js.log);
    } else {
      let testtime = SettingFormLoad |> dispatch;
      let timeId = searchAJax();
      Some(
        () => {
          testtime;
          timeId;
        },
      );
    }
  );

  let clickItemTab = useCallback(i => ClickItemTab(i) |> dispatch);

  let insertAJax = () =>
    Js.Promise.(
      iIconData(state.items, state.qaitems, "newid" |> Locals.select)
      |> Axiosapi.Icon.insert
      |> then_(response => {
           {
             response##data##status
             |> Status.statusModule
             |> barShowRestoreAction;
             ActionShowProgress |> dispatch;
           }
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickBottomNavigation =
    useCallback(bi
      //ClickBottomNavigation(bi) |> dispatch;
      =>
        if (bi == 0) {
          ActionShowProgress |> dispatch;
          ActionShowProgress |> dispatch;
        } else if (bi == 1) {
          ActionShowProgress |> dispatch;
          insertAJax();
        }
      );

  <>
    <NewFacetube
      showProgress={state.showProgress}
      error={state.error}
      width="100"
      bottom="56">
      <GridContainer direction="column" justify="center" alignItem="stretch">
        <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
          <GridContainer direction="row" justify="start" alignItem="center">
            <GridItem
              top="0" right="0" bottom="0" left="0" xs="auto" maxWidth="25%">
              <Tabs id="icon-" index={state.index} height="3">
                {state.tabitems
                 |> List.mapi((i, tabitem) =>
                      <Tab
                        tabShow={tabitem.tabShow}
                        borderRadius="15"
                        id={"icon-" ++ string_of_int(i)}
                        animationName="none"
                        onClick={_ => i |> clickItemTab}>
                        <IconAction
                          animation="leftRight"
                          src={tabitem.tabImage}
                        />
                      </Tab>
                    )
                 |> Array.of_list
                 |> array}
              </Tabs>
            </GridItem>
          </GridContainer>
        </GridItem>
        <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
          <GridContainer direction="row" justify="start" alignItem="center">
            {switch (state.index) {
             | 0 =>
               state.items
               |> Array.map(item =>
                    <IconForm icon={item.icon} value={item.value} />
                  )
               |> array
             | _ =>
               state.qaitems
               |> Array.map(qaitem =>
                    <IconForm icon={qaitem.icon} value={qaitem.value} />
                  )
               |> array
             }}
          </GridContainer>
        </GridItem>
      </GridContainer>
    </NewFacetube>
    {state.error
       ? null
       : <Navigation
           style={ReactDOMRe.Style.combine(
             marginAuto,
             ReactDOMRe.Style.make(
               ~position="fixed",
               ~maxWidth="770px",
               ~right="0",
               ~bottom="0",
               ~transition="left 195ms cubic-bezier(0.4, 0, 0.6, 1) 0ms",
               (),
             ),
           )}
           className="facetubenavigation">
           {state.bottomitems
            |> List.mapi((bi, bottomitem) =>
                 <BottomNavigation
                   actionShow={bottomitem.actionShow}
                   disabled={state.showProgress}
                   onClick={_ => bi |> clickBottomNavigation}
                   icon={bottomitem.icon}
                   tile={bottomitem.tile}
                 />
               )
            |> Array.of_list
            |> array}
         </Navigation>}
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {state.youtubeText |> string} </span>, null)
    </SnackbarYoutube>
  </>;
};
