open React;
open Icons;
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
    {icon: addBlack, value: "add"},
    {icon: arrowUpBlack, value: "arrowUp"},
    {icon: assistantBlack, value: "assistant"},
    {icon: arrowDownBlack, value: "arrowDown"},
    {icon: attachFileBlack, value: "attachFile"},
    {icon: accesstimeBlack, value: "accesstime"},
    {icon: accountBoxBlack, value: "accountBox"},
    {icon: accountTreeBlack, value: "accountTree"},
    {icon: announcementBlack, value: "announcement"},
    {icon: arrowBackIosBlack, value: "arrowBackIos"},
    {icon: assignmentIndBlack, value: "assignmentInd"},
    {icon: arrowForwardIosBlack, value: "arrowForwardIos"},
    {icon: barChartBlack, value: "barChart"},
    {icon: brightness4Black, value: "brightness4"},
    {icon: brightnessLowBlack, value: "brightnessLow"},
    {icon: brightnessHighBlack, value: "brightnessHigh"},
    {icon: cancelBlack, value: "cancel"},
    {icon: clearBlack, value: "clear"},
    {icon: createBlack, value: "create"},
    {icon: checkBoxBlack, value: "checkBox"},
    {icon: colorLensBlack, value: "colorLens"},
    {icon: cardTravelBlack, value: "cardTravel"},
    {icon: chatBubbleBlack, value: "chatBubble"},
    {icon: collectionsBlack, value: "collections"},
    {icon: cloudDownloadBlack, value: "cloudDownload"},
    {icon: checkBoxOutlineBlankBlack, value: "checkBoxOutlineBlank"},
    {icon: doneBlack, value: "done"},
    {icon: deleteBlack, value: "delete"},
    {icon: dateRangeBlack, value: "dateRange"},
    {icon: descriptionBlack, value: "description"},
    {icon: editBlack, value: "edit"},
    {icon: emailBlack, value: "email"},
    {icon: eventBlack, value: "event"},
    {icon: errorBlack, value: "error"},
    {icon: flagBlack, value: "flag"},
    {icon: fileCopyBlack, value: "fileCopy"},
    {icon: formatBoldBlack, value: "formatBold"},
    {icon: formatSizeBlack, value: "formatSize"},
    {icon: formatClearBlack, value: "formatClear"},
    {icon: formatItalicBlack, value: "formatItalic"},
    {icon: formatUnderlinedBlack, value: "formatUnderlined"},
    {icon: formatAlignLeftBlack, value: "formatAlignLeft"},
    {icon: formatAlignRightBlack, value: "formatAlignRight"},
    {icon: formatAlignCenterBlack, value: "formatAlignCenter"},
    {icon: formatListBulletedBlack, value: "formatListBulleted"},
    {icon: formatListNumberedBlack, value: "formatListNumbered"},
    {icon: formatIndentDecreaseBlack, value: "formatIndentDecrease"},
    {icon: formatIndentIncreaseBlack, value: "formatIndentIncrease"},
    {icon: groupBlack, value: "group"},
    {icon: homeBlack, value: "home"},
    {icon: helpBlack, value: "help"},
    {icon: helpOutlineBlack, value: "helpOutline"},
    {icon: imageBlack, value: "image"},
    {icon: inputBlack, value: "input"},
    {icon: importExportBlack, value: "importExport"},
    {icon: importContactsBlack, value: "importContacts"},
    {icon: insertInvitationBlack, value: "insertInvitation"},
    {icon: keyboardBlack, value: "keyboardBlack"},
    {icon: keyboardBackspaceBlack, value: "keyboardBackspace"},
    {icon: keyboardArrowRightBlack, value: "keyboardArrowRight"},
    {icon: listBlack, value: "list"},
    {icon: lockBlack, value: "lock"},
    {icon: languageBlack, value: "language"},
    {icon: libraryBooksBlack, value: "libraryBooks"},
    {icon: localActivityBlack, value: "localActivity"},
    {icon: mapBlack, value: "map"},
    {icon: mailBlack, value: "mail"},
    {icon: menuBlack, value: "menu"},
    {icon: menuBookBlack, value: "menuBook"},
    {icon: moreVertBlack, value: "moreVert"},
    {icon: monetizationOnBlack, value: "monetizationOn"},
    {icon: notesBlack, value: "notes"},
    {icon: nightsStayBlack, value: "nightsStay"},
    {icon: notificationsBlack, value: "notifications"},
    {icon: notificationsActiveBlack, value: "notificationsActive"},
    {icon: notificationImportantBlack, value: "notificationImportant"},
    {icon: photoBlack, value: "photo"},
    {icon: personBlack, value: "person"},
    {icon: peopleBlack, value: "people"},
    {icon: personAddBlack, value: "personAdd"},
    {icon: privacyTipBlack, value: "privacyTip"},
    {icon: questionAnswerBlack, value: "questionAnswer"},
    {icon: restoreBlack, value: "restore"},
    {icon: refreshBlack, value: "refresh"},
    {icon: radioButtonCheckedBlack, value: "radioButtonChecked"},
    {icon: radioButtonUncheckedBlack, value: "radioButtonUnchecked"},
    {icon: sendBlack, value: "send"},
    {icon: saveBlack, value: "save"},
    {icon: storeBlack, value: "store"},
    {icon: shareBlack, value: "share"},
    {icon: searchBlack, value: "search"},
    {icon: settingsBlack, value: "settings"},
    {icon: storefrontBlack, value: "storefront"},
    {icon: securityBlack, value: "security"},
    {icon: shortTextBlack, value: "shortText"},
    {icon: strikethroughSBlack, value: "strikethroughS"},
    {icon: settingsApplicationsBlack, value: "settingsApplications"},
    {icon: tourBlack, value: "tour"},
    {icon: todayBlack, value: "today"},
    {icon: translateBlack, value: "translate"},
    {icon: textFormatBlack, value: "textFormat"},
    {icon: textFieldsBlack, value: "textFields"},
    {icon: wifiBlack, value: "wifi"},
    {icon: wifiOffBlack, value: "wifiOff"},
  |],
  qaitems: [|
    {icon: shortTextBlack, value: "text"},
    {icon: radioButtonCheckedBlack, value: "radio"},
    {icon: checkBoxBlack, value: "checkbox"},
    {icon: notesBlack, value: "textarea"},
    {icon: imageBlack, value: "image"},
    {icon: collectionsBlack, value: "collections"},
  |],
  tabitems: [
    {tabShow: true, tabImage: homeBlack},
    {tabShow: false, tabImage: homeBlack},
  ],
  index: 0,
  bottomitems: [
    {actionShow: true, icon: settingsApplicationsBlack, tile: "Settings"},
    {actionShow: true, icon: saveBlack, tile: "Save"},
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
      "newid"
      |> Locals.select
      |> iIconData(state.items, state.qaitems)
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
               ~left="0",
               ~transition="left 195ms cubic-bezier(0.4, 0, 0.6, 1) 0ms",
               (),
             ),
           )}>
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
