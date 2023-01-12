// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as ReactIntl from "react-intl";
import * as Path$BtsCore from "../../features/Path.bs.js";
import * as Icons$BtsCore from "../../material-ui/icon/Icons.bs.js";
import * as List_$BtsCore from "../../material-ui/core/List_/List_.bs.js";
import * as Drawer$BtsCore from "../../material-ui/core/Drawer/Drawer.bs.js";
import * as OutSide$BtsCore from "../../styles/OutSide/OutSide.bs.js";
import * as Setting$BtsCore from "../../setting/Setting.bs.js";
import * as ListIcon$BtsCore from "../../material-ui/core/ListItem/ListIcon.bs.js";
import * as Together$BtsCore from "../../styles/Together/Together.bs.js";
import * as ReasonReactRouter from "reason-react/src/ReasonReactRouter.js";
import * as Typography$BtsCore from "../../material-ui/core/Typography/Typography.bs.js";
import * as IconGeneral$BtsCore from "../../material-ui/core/IconStyle/IconGeneral.bs.js";
import * as ProgressLinear$BtsCore from "../../material-ui/core/Progress/ProgressLinear.bs.js";

((require('../../../scss/example/Facebook/newFacebook.scss')));

function reducer(state, action) {
  if (action) {
    return {
            formLoad: state.formLoad,
            formWidth: action[0],
            formHeight: action[1]
          };
  } else {
    return {
            formLoad: !state.formLoad,
            formWidth: state.formWidth,
            formHeight: state.formHeight
          };
  }
}

var initialState = {
  formLoad: false,
  formWidth: 0,
  formHeight: 0
};

function widths(width) {
  if (width !== undefined) {
    return width + "%";
  } else {
    return "95%";
  }
}

function bottoms(bottom) {
  if (bottom !== undefined) {
    return bottom + "px";
  } else {
    return "0px";
  }
}

function NewFacebook(Props) {
  var showProgress = Props.showProgress;
  var error = Props.error;
  var width = Props.width;
  var bottom = Props.bottom;
  var children = Props.children;
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  var state = match[0];
  React.useEffect((function () {
          if (state.formLoad) {
            return (function (param) {
                      console.log("action");
                      
                    });
          }
          Curry._1(dispatch, /* SettingFormLoad */0);
          var formId = Curry._1(dispatch, /* SettingFormWidth */[
                window.innerWidth,
                window.innerHeight
              ]);
          return (function (param) {
                    return formId;
                  });
        }));
  var handleResize = function ($$event) {
    return Curry._1(dispatch, /* SettingFormWidth */[
                $$event.currentTarget.innerWidth,
                $$event.currentTarget.innerHeight
              ]);
  };
  React.useEffect((function () {
          window.addEventListener("resize", handleResize, true);
          return (function (param) {
                    
                  });
        }), ([]));
  return React.createElement(React.Fragment, undefined, Setting$BtsCore.disabledObjects(showProgress) ? React.createElement(ProgressLinear$BtsCore.make, {
                    style: OutSide$BtsCore.progressFixed
                  }) : null, React.createElement(Drawer$BtsCore.make, {
                  style: {
                    borderRight: "0",
                    overflow: "hidden",
                    whiteSpace: "nowrap",
                    transition: "width 225ms cubic-bezier(0.4, 0, 0.6, 1) 0ms"
                  },
                  top: "60",
                  left: "0",
                  width: state.formWidth < 1100 ? "0px" : "320px",
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
                            onClick: (function (param) {
                                return ReasonReactRouter.push(Path$BtsCore.homePath);
                              }),
                            children: /* tuple */[
                              React.createElement(IconGeneral$BtsCore.make, {
                                    src: Icons$BtsCore.homeBlack
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
                            onClick: (function (param) {
                                return ReasonReactRouter.push(Path$BtsCore.homePath);
                              }),
                            children: /* tuple */[
                              React.createElement(IconGeneral$BtsCore.make, {
                                    src: Icons$BtsCore.homeBlack
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
                }), React.createElement("main", {
                  className: "fbmainlayout",
                  style: Object.assign(({}), OutSide$BtsCore.mainTube, {
                        bottom: bottoms(bottom),
                        top: "80px",
                        transition: "left 225ms cubic-bezier(0.4, 0, 0.6, 1) 0ms, right 225ms cubic-bezier(0.4, 0, 0.6, 1) 0ms"
                      })
                }, React.createElement("div", {
                      style: Together$BtsCore.divScrollbar
                    }, React.createElement("div", {
                          style: Object.assign(({}), Together$BtsCore.marginAuto, {
                                maxWidth: widths(width),
                                width: widths(width),
                                flexBasis: widths(width)
                              })
                        }, Setting$BtsCore.disabledObjects(error) ? React.createElement("div", {
                                style: OutSide$BtsCore.errorForm
                              }, React.createElement(Typography$BtsCore.make, {
                                    variant: "tile",
                                    color: "rgba(255,0,0,0.8)",
                                    fontSize: "x-large",
                                    children: "UNDEFINED THIS PAGE"
                                  })) : children[0]))), React.createElement(Drawer$BtsCore.make, {
                  style: {
                    borderLeft: "0",
                    overflowX: "hidden",
                    whiteSpace: "nowrap",
                    zIndex: "1",
                    transition: "width 195ms cubic-bezier(0.4, 0, 0.6, 1) 0ms"
                  },
                  top: "60",
                  right: "0",
                  width: state.formWidth < 901 ? "0px" : "320px",
                  height: "64",
                  location: "right",
                  children: children[1]
                }));
}

var make = NewFacebook;

export {
  reducer ,
  initialState ,
  widths ,
  bottoms ,
  make ,
  
}
/*  Not a pure module */
