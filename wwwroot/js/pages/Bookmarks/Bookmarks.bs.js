// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as ReactIntl from "react-intl";
import * as Path$BtsCore from "../../features/Path.bs.js";
import * as Icons$BtsCore from "../../material-ui/icon/Icons.bs.js";
import * as List_$BtsCore from "../../material-ui/core/List_/List_.bs.js";
import * as Avatar$BtsCore from "../../material-ui/core/Avatar/Avatar.bs.js";
import * as Drawer$BtsCore from "../../material-ui/core/Drawer/Drawer.bs.js";
import * as ListIcon$BtsCore from "../../material-ui/core/ListItem/ListIcon.bs.js";
import * as ReasonReactRouter from "reason-react/src/ReasonReactRouter.js";
import * as IconButton$BtsCore from "../../material-ui/core/IconButton/IconButton.bs.js";
import * as Typography$BtsCore from "../../material-ui/core/Typography/Typography.bs.js";
import * as IconGeneral$BtsCore from "../../material-ui/core/IconStyle/IconGeneral.bs.js";
import * as ObjectFormat$BtsCore from "../../controls/ObjectFormat.bs.js";

function Bookmarks(Props) {
  return React.createElement(Drawer$BtsCore.make, {
              style: {
                borderRight: "0",
                overflow: "hidden",
                whiteSpace: "nowrap",
                transition: "width 225ms cubic-bezier(0.4, 0, 0.6, 1) 0ms"
              },
              top: "60",
              left: "0",
              width: "100vw",
              height: "64",
              zIndex: "1000",
              location: "left",
              children: React.createElement(List_$BtsCore.make, {
                    top: "16",
                    children: null
                  }, React.createElement(ListIcon$BtsCore.make, {
                        style: {
                          height: "52px"
                        },
                        enterBackgroundColor: "rgba(0,0,0,0.12)",
                        downBackgroundColor: "rgba(0,0,0,0.06)",
                        topLeft: "20",
                        topRight: "20",
                        bottomRight: "20",
                        bottomLeft: "20",
                        right: "0",
                        left: "0",
                        children: /* tuple */[
                          React.createElement(Avatar$BtsCore.make, {
                                top: "0",
                                right: "0",
                                bottom: "0",
                                left: "0",
                                color: "#909090",
                                backgroundColor: "rgba(0,0,0,0.08)",
                                children: ObjectFormat$BtsCore.checkObjects(localStorage.getItem("name"))
                              }),
                          React.createElement(Typography$BtsCore.make, {
                                variant: "subheading",
                                children: ObjectFormat$BtsCore.checkObjects(localStorage.getItem("allname"))
                              })
                        ]
                      }), React.createElement(ListIcon$BtsCore.make, {
                        style: {
                          height: "52px"
                        },
                        enterBackgroundColor: "rgba(0,0,0,0.12)",
                        downBackgroundColor: "rgba(0,0,0,0.06)",
                        topLeft: "20",
                        topRight: "20",
                        bottomRight: "20",
                        bottomLeft: "20",
                        right: "0",
                        left: "0",
                        onClick: (function (param) {
                            return ReasonReactRouter.push(Path$BtsCore.homePath);
                          }),
                        children: /* tuple */[
                          React.createElement(IconButton$BtsCore.make, {
                                backgroundColor: "rgba(0,0,0,0.08)",
                                children: React.createElement(IconGeneral$BtsCore.make, {
                                      src: Icons$BtsCore.homeBlack
                                    })
                              }),
                          React.createElement(Typography$BtsCore.make, {
                                variant: "subheading",
                                children: React.createElement(ReactIntl.FormattedMessage, {
                                      id: "Path.home",
                                      defaultMessage: "Home"
                                    })
                              })
                        ]
                      }), React.createElement(ListIcon$BtsCore.make, {
                        style: {
                          height: "52px"
                        },
                        enterBackgroundColor: "rgba(0,0,0,0.12)",
                        downBackgroundColor: "rgba(0,0,0,0.06)",
                        topLeft: "20",
                        topRight: "20",
                        bottomRight: "20",
                        bottomLeft: "20",
                        right: "0",
                        left: "0",
                        onClick: (function (param) {
                            return ReasonReactRouter.push(Path$BtsCore.homePath);
                          }),
                        children: /* tuple */[
                          React.createElement(IconButton$BtsCore.make, {
                                backgroundColor: "rgba(0,0,0,0.08)",
                                children: React.createElement(IconGeneral$BtsCore.make, {
                                      src: Icons$BtsCore.homeBlack
                                    })
                              }),
                          React.createElement(Typography$BtsCore.make, {
                                variant: "subheading",
                                children: React.createElement(ReactIntl.FormattedMessage, {
                                      id: "Path.home",
                                      defaultMessage: "Home"
                                    })
                              })
                        ]
                      }))
            });
}

var make = Bookmarks;

export {
  make ,
  
}
/* react Not a pure module */
