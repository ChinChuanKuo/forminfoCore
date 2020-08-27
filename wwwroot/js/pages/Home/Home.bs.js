// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Block from "bs-platform/lib/es6/block.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Data$BtsCore from "../../features/Data.bs.js";
import * as Axiosapi$BtsCore from "../../features/Axiosapi.bs.js";
import * as GridItem$BtsCore from "../../material-ui/core/Grid/GridItem.bs.js";
import * as Together$BtsCore from "../../styles/Together/Together.bs.js";
import * as NewFacetube$BtsCore from "../../example/Facebook/NewFacetube.bs.js";
import * as SnackbarYoutube$BtsCore from "../../material-ui/core/Snackbar/SnackbarYoutube.bs.js";

((require('../../../scss/pages/Together/together.scss')));

function reducer(state, action) {
  if (typeof action === "number") {
    switch (action) {
      case /* SettingErrorLoad */0 :
          return {
                  formLoad: state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  showProgress: state.showProgress,
                  error: !state.error,
                  insert: state.insert,
                  update: state.update,
                  delete: state.delete,
                  export: state.export,
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* SettingFormLoad */1 :
          return {
                  formLoad: !state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  showProgress: state.showProgress,
                  error: state.error,
                  insert: state.insert,
                  update: state.update,
                  delete: state.delete,
                  export: state.export,
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* ActionShowProgress */2 :
          return {
                  formLoad: state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  showProgress: !state.showProgress,
                  error: state.error,
                  insert: state.insert,
                  update: state.update,
                  delete: state.delete,
                  export: state.export,
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      
    }
  } else {
    switch (action.tag | 0) {
      case /* SettingFormWidth */0 :
          return {
                  formLoad: state.formLoad,
                  formWidth: action[0],
                  formHeight: action[1],
                  showProgress: state.showProgress,
                  error: state.error,
                  insert: state.insert,
                  update: state.update,
                  delete: state.delete,
                  export: state.export,
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* ActionPermissItems */1 :
          return {
                  formLoad: state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  showProgress: state.showProgress,
                  error: state.error,
                  insert: action[0],
                  update: action[1],
                  delete: action[2],
                  export: action[3],
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* ActionSnackBar */2 :
          return {
                  formLoad: state.formLoad,
                  formWidth: state.formWidth,
                  formHeight: state.formHeight,
                  showProgress: state.showProgress,
                  error: state.error,
                  insert: state.insert,
                  update: state.update,
                  delete: state.delete,
                  export: state.export,
                  showYoutube: action[1],
                  youtubeText: action[0]
                };
      
    }
  }
}

var initialState = {
  formLoad: false,
  formWidth: 0,
  formHeight: 0,
  showProgress: true,
  error: false,
  insert: false,
  update: false,
  delete: false,
  export: false,
  showYoutube: false,
  youtubeText: ""
};

function defaultFloat(value) {
  if (value === "") {
    return "0.0";
  } else {
    return value;
  }
}

function Home(Props) {
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  var state = match[0];
  React.useRef(null);
  var permissAJax = function (param) {
    Axiosapi$BtsCore.Form.permiss(Data$BtsCore.userData(localStorage.getItem("newid"))).then((function (response) {
              return Promise.resolve((Curry._1(dispatch, /* ActionPermissItems */Block.__(1, [
                                  response.data.insert,
                                  response.data.update,
                                  response.data.delete,
                                  response.data.export
                                ])), Curry._1(dispatch, /* ActionShowProgress */2)));
            })).catch((function (error) {
            return Promise.resolve((console.log(error), undefined));
          }));
    
  };
  React.useEffect((function () {
          var match = state.formLoad;
          if (match) {
            return (function (param) {
                      console.log("action");
                      
                    });
          }
          Curry._1(dispatch, /* SettingFormLoad */1);
          Curry._1(dispatch, /* SettingFormWidth */Block.__(0, [
                  window.innerWidth,
                  window.innerHeight
                ]));
          var timeId = permissAJax(undefined);
          return (function (param) {
                    return timeId;
                  });
        }));
  var handleResize = function ($$event) {
    return Curry._1(dispatch, /* SettingFormWidth */Block.__(0, [
                  $$event.currentTarget.innerWidth,
                  $$event.currentTarget.innerHeight
                ]));
  };
  React.useEffect((function () {
          window.addEventListener("resize", handleResize, true);
          return (function (param) {
                    
                  });
        }), ([]));
  return React.createElement(React.Fragment, undefined, React.createElement(NewFacetube$BtsCore.make, {
                  showProgress: state.showProgress,
                  error: state.error,
                  children: React.createElement(GridItem$BtsCore.make, {
                        style: Together$BtsCore.marginAuto,
                        top: "0",
                        right: "32",
                        bottom: "0",
                        left: "32",
                        xs: "12",
                        maxWidth: "770px",
                        children: null
                      })
                }), React.createElement(SnackbarYoutube$BtsCore.make, {
                  showYoutube: state.showYoutube,
                  position: "bottomLeft",
                  children: /* tuple */[
                    React.createElement("span", undefined, state.youtubeText),
                    null
                  ]
                }));
}

var make = Home;

export {
  reducer ,
  initialState ,
  defaultFloat ,
  make ,
  
}
/*  Not a pure module */
